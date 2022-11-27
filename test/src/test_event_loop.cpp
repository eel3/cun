// -*- coding: utf-8-with-signature-dos -*-
// vim:fileencoding=utf-8:ff=dos
//
// Test code: Event loop toolbox.

// C++ standard library
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <sstream>
#include <utility>

// C++ user library
#include "event_loop.hpp"
#include "unittest.hpp"

namespace {

// C++ standard library
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

/* ---------------------------------------------------------------------- */
/* Test code: have no event. */
/* ---------------------------------------------------------------------- */

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

/* ---------------------------------------------------------------------- */
/* Test code: without a context object. */
/* ---------------------------------------------------------------------- */

bool test_no_ctx_1(void *ctx, void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_1: ctx = " << ctx << " : results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return false;
}

bool test_no_ctx_2(void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_2: results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return true;
}

bool test_no_ctx_3(void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_3: results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return false;
}

void test_no_ctx(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - without a context object.");
    CUN_UNITTEST_NL(ut);

    std::map<EventType, EventLoop<EventType>::event_proc> entry {
        // function with a unused context pointer.
        make_pair(EventType::on_test_1, test_no_ctx_1),

#define ENTRY(type, fn) \
        make_pair(EventType::type, [](void *, void *args, void *results) { return fn(args, results); })

        // function without a unused context pointer.
        ENTRY(on_test_2, test_no_ctx_2),
        ENTRY(on_test_3, test_no_ctx_3),

#undef ENTRY
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

/* ---------------------------------------------------------------------- */
/* Test code: with a context object. */
/* ---------------------------------------------------------------------- */

struct Context final {
    int32_t count = 0;
};

bool test_with_ctx_1(Context *ctx, void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_1: results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return false;
}

bool test_with_ctx_2(Context *ctx, void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_2: results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return true;
}

bool test_with_ctx_3(Context *ctx, void *args, void *results)
{
    auto& ut = *static_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_3: results = " << results;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return false;
}

void test_with_ctx(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - with a context object.");
    CUN_UNITTEST_NL(ut);

    std::map<EventType, EventLoop<EventType, Context *>::event_proc> entry {
        make_pair(EventType::on_test_1, test_with_ctx_1),
        make_pair(EventType::on_test_2, test_with_ctx_2),
        make_pair(EventType::on_test_3, test_with_ctx_3),
    };

    CUN_UNITTEST_EXEC(ut, Context context);
    CUN_UNITTEST_EXEC(ut, EventLoop<EventType, Context *> el { entry, &context });
    CUN_UNITTEST_EXEC(ut, auto results = reinterpret_cast<void *>(static_cast<uintptr_t>(0xDEADBEEF)));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, context.count == 0);
    CUN_UNITTEST_EVAL(ut, el.post_event(EventType::on_test_1, &ut));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_2, &ut, results));
    CUN_UNITTEST_EVAL(ut, !el.send_event(EventType::on_test_3, &ut, results));
    CUN_UNITTEST_EVAL(ut, context.count == 3);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_RESET(ut);
}

/* ---------------------------------------------------------------------- */
/* Test code: inherited class. */
/* ---------------------------------------------------------------------- */

class InheritedEventLoop final : private EventLoop<EventType, InheritedEventLoop *> {
private:
    void *ARGS = reinterpret_cast<void *>(static_cast<uintptr_t>(0x32211800));
    void *RESULTS = reinterpret_cast<void *>(static_cast<uintptr_t>(0xDEADBEEF));

    UnitTest& m_ut;

    static bool on_test_1(InheritedEventLoop *thiz, void *args, void *results) {
        ostringstream oss;
        oss << "test_1: thiz = " << thiz << " : args = " << args << " : results = " << results;
        CUN_UNITTEST_ECHO(thiz->m_ut, oss.str().c_str());

        return false;
    }

    bool on_test_2(InheritedEventLoop *thiz, void *args, void *results) {
        ostringstream oss;
        oss << "test_2: thiz = " << thiz << " : args = " << args << " : results = " << results;
        CUN_UNITTEST_ECHO(thiz->m_ut, oss.str().c_str());
        CUN_UNITTEST_EVAL(m_ut, thiz == this);

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
            // static member function with a context object.
            make_pair(EventType::on_test_1, on_test_1),

            // non-static member function with a context object.
            make_pair(EventType::on_test_2, [this](InheritedEventLoop *thiz, void *args, void *results) {
                return on_test_2(thiz, args, results);
            }),

#define ENTRY(type, fn) \
        make_pair(EventType::type, [this](InheritedEventLoop *, void *args, void *results) { return fn(args, results); })

            // non-static member function without a context object.
            ENTRY(on_test_3, on_test_3),
            ENTRY(on_destroy, on_destroy),

#undef ENTRY
        }, this },
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

/* ---------------------------------------------------------------------- */
/* Main routine. */
/* ---------------------------------------------------------------------- */

int main()
{
    auto ut = CUN_UNITTEST_MAKE();

    test_no_event(ut);
    test_no_ctx(ut);
    test_with_ctx(ut);
    test_inherited_class(ut);

    return EXIT_SUCCESS;
}
