// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Event loop toolbox.

// C++ standard library
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

// C++ user library
#include "event_loop.hpp"
#include "unittest.hpp"

namespace {

// C++ standard library
using std::endl;
using std::make_pair;
using std::ostringstream;
using std::uintptr_t;

// C++ user library
using namespace cun;

enum class EventType {
    on_test_1,
    on_test_2,
    on_test_3,
    on_destroy,
    on_destroy_event_loop
};

void test_no_event(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - have no event.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, EventLoop<EventType> el);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, (void) el);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

bool test_1(void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_1: results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return false;
}

bool test_2(void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_2: results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return true;
}

bool test_3(void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_3: results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return false;
}

void test_with_event(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - have some events.");
    CUN_UNITTEST_NL(ut);

    std::map<EventType, EventLoop<EventType>::event_proc> entry {
        make_pair(EventType::on_test_1, test_1),
        make_pair(EventType::on_test_2, test_2),
        make_pair(EventType::on_test_3, test_3),
    };

    CUN_UNITTEST_EXEC(ut, EventLoop<EventType> el { entry });
    CUN_UNITTEST_EXEC(ut, auto results = reinterpret_cast<void *>(static_cast<uintptr_t>(0xDEADBEEF)));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, el.post_event(EventType::on_test_1, &ut));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_2, &ut, results));
    CUN_UNITTEST_EVAL(ut, !el.send_event(EventType::on_test_3, &ut, results));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

class InheritedEventLoop final : private EventLoop<EventType> {
private:
    void *ARGS = reinterpret_cast<void *>(static_cast<uintptr_t>(0x32211800));
    void *RESULTS = reinterpret_cast<void *>(static_cast<uintptr_t>(0xDEADBEEF));

    UnitTest& m_ut;

    bool on_test_1(void *args, void *results) {
        ostringstream oss;
        oss << "test_1: args = " << args << " : results = " << results;
        CUN_UNITTEST_ECHO(m_ut, oss.str().c_str());

        return false;
    }

    bool on_test_2(void *args, void *results) {
        ostringstream oss;
        oss << "test_2: args = " << args << " : results = " << results;
        CUN_UNITTEST_ECHO(m_ut, oss.str().c_str());

        return true;
    }

    bool on_test_3(void *args, void *results) {
        ostringstream oss;
        oss << "test_3: args = " << args << " : results = " << results;
        CUN_UNITTEST_ECHO(m_ut, oss.str().c_str());

        return false;
    }

    bool on_destroy(void *, void *) {
        CUN_UNITTEST_ECHO(m_ut, "on_destroy");
        return true;
    }

public:
    explicit InheritedEventLoop(UnitTest& ut) :
        EventLoop {{
#define ENTRY(type, fn) \
        make_pair(EventType::type, [this](void *args, void *results) { return fn(args, results); })

            ENTRY(on_test_1, on_test_1),
            ENTRY(on_test_2, on_test_2),
            ENTRY(on_test_3, on_test_3),
            ENTRY(on_destroy, on_destroy),

#undef ENTRY
        }},
        m_ut { ut } {}

    virtual ~InheritedEventLoop() {
        (void) send_event(EventType::on_destroy);
    }

    bool test_1() {
        return post_event(EventType::on_test_1, ARGS);
    }

    bool test_2() {
        return send_event(EventType::on_test_2, ARGS, RESULTS);
    }

    bool test_3() {
        return send_event(EventType::on_test_3, ARGS, RESULTS);
    }
};

void test_inherited_class(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - inherited class.");
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, auto el = std::make_unique<InheritedEventLoop>(ut));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, el->test_1());
    CUN_UNITTEST_EVAL(ut, el->test_2());
    CUN_UNITTEST_EVAL(ut, !el->test_3());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EXEC(ut, el.reset());
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

} // namespace

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_no_event(ut);
    test_with_event(ut);
    test_inherited_class(ut);

    return EXIT_SUCCESS;
}
