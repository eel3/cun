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
using cun::EventLoop;
using cun::UnitTest;

enum class EventType {
    on_test_1,
    on_test_2,
    on_test_3,
    on_destroy
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

bool test_no_ctx_1(void *ctx, std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);
    const auto res = results.has_value() ? "NG" : "(empty)";

    ostringstream oss;
    oss << "test_1: ctx = " << ctx << " : results = " << res;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return false;
}

bool test_no_ctx_2(std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_2: results = " << std::any_cast<void *>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return true;
}

bool test_no_ctx_3(std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_3: results = " << std::any_cast<void *>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return false;
}

void test_no_ctx(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - without a context object.");
    CUN_UNITTEST_NL(ut);

    EventLoop<EventType>::event_entry entry {
        // function with a unused context pointer.
        make_pair(EventType::on_test_1, test_no_ctx_1),

#define ENTRY(type, fn) \
        make_pair(EventType::type, [](void *, std::any& args, std::any& results) { return fn(args, results); })

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
/* Test code: with a context object (using raw pointer). */
/* ---------------------------------------------------------------------- */

struct Context final {
    int32_t count = 0;
};

bool test_with_ctx_rawptr_1(Context *ctx, std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);
    const auto res = results.has_value() ? "NG" : "(empty)";

    ostringstream oss;
    oss << "test_1: results = " << res;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return false;
}

bool test_with_ctx_rawptr_2(Context *ctx, std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_2: results = " << std::any_cast<void *>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return true;
}

bool test_with_ctx_rawptr_3(Context *ctx, std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_3: results = " << std::any_cast<void *>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return false;
}

void test_with_ctx_rawptr(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - with a context object (using raw pointer).");
    CUN_UNITTEST_NL(ut);

    EventLoop<EventType, Context *>::event_entry entry {
        make_pair(EventType::on_test_1, test_with_ctx_rawptr_1),
        make_pair(EventType::on_test_2, test_with_ctx_rawptr_2),
        make_pair(EventType::on_test_3, test_with_ctx_rawptr_3),
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
/* Test code: with a context object (using smart pointer). */
/* ---------------------------------------------------------------------- */

using SharedContext = std::shared_ptr<Context>;

bool test_with_ctx_smartptr_1(SharedContext ctx, std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);
    const auto res = results.has_value() ? "NG" : "(empty)";

    ostringstream oss;
    oss << "test_1: results = " << res;
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return false;
}

bool test_with_ctx_smartptr_2(SharedContext ctx, std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_2: results = " << std::any_cast<void *>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return true;
}

bool test_with_ctx_smartptr_3(SharedContext ctx, std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_3: results = " << std::any_cast<void *>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());
    CUN_UNITTEST_EXEC(ut, ctx->count++);

    return false;
}

void test_with_ctx_smartptr(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - with a context object (using smart pointer).");
    CUN_UNITTEST_NL(ut);

    EventLoop<EventType, SharedContext>::event_entry entry {
        make_pair(EventType::on_test_1, test_with_ctx_smartptr_1),
        make_pair(EventType::on_test_2, test_with_ctx_smartptr_2),
        make_pair(EventType::on_test_3, test_with_ctx_smartptr_3),
    };

    CUN_UNITTEST_EXEC(ut, auto context = std::make_shared<Context>());
    CUN_UNITTEST_EXEC(ut, EventLoop<EventType, SharedContext> el { entry, context });
    CUN_UNITTEST_EXEC(ut, auto results = reinterpret_cast<void *>(static_cast<uintptr_t>(0xDEADBEEF)));
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, context->count == 0);
    CUN_UNITTEST_EVAL(ut, el.post_event(EventType::on_test_1, &ut));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_2, &ut, results));
    CUN_UNITTEST_EVAL(ut, !el.send_event(EventType::on_test_3, &ut, results));
    CUN_UNITTEST_EVAL(ut, context->count == 3);
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

    static bool on_test_1(InheritedEventLoop *thiz, std::any& args, std::any& results) {
        const auto res = results.has_value() ? "NG" : "(empty)";
        ostringstream oss;
        oss << "test_1: thiz = " << thiz << " : args = " << std::any_cast<void *>(args) << " : results = " << res;
        CUN_UNITTEST_ECHO(thiz->m_ut, oss.str().c_str());

        return false;
    }

    bool on_test_2(InheritedEventLoop *thiz, std::any& args, std::any& results) {
        ostringstream oss;
        oss << "test_2: thiz = " << thiz << " : args = " << std::any_cast<void *>(args) << " : results = " << std::any_cast<void *>(results);
        CUN_UNITTEST_ECHO(thiz->m_ut, oss.str().c_str());
        CUN_UNITTEST_EVAL(m_ut, thiz == this);

        return true;
    }

    bool on_test_3(std::any& args, std::any& results) {
        ostringstream oss;
        oss << "test_3: args = " << std::any_cast<void *>(args) << " : results = " << std::any_cast<void *>(results);
        CUN_UNITTEST_ECHO(m_ut, oss.str().c_str());

        return false;
    }

    bool on_destroy(std::any& args, std::any& results) {
        const auto arg = args.has_value() ? "NG" : "(empty)";
        const auto res = results.has_value() ? "NG" : "(empty)";
        ostringstream oss;
        oss << "on_destroy: args = " << arg << " : results = " << res;
        CUN_UNITTEST_ECHO(m_ut, oss.str().c_str());

        return true;
    }

public:
    explicit InheritedEventLoop(UnitTest& ut) :
        EventLoop {{
            // static member function with a context object.
            make_pair(EventType::on_test_1, on_test_1),

            // non-static member function with a context object.
            make_pair(EventType::on_test_2, [this](InheritedEventLoop *thiz, std::any& args, std::any& results) {
                return on_test_2(thiz, args, results);
            }),

#define ENTRY(type, fn) \
        make_pair(EventType::type, [this](InheritedEventLoop *, std::any& args,std::any& results) { return fn(args, results); })

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

/* ---------------------------------------------------------------------- */
/* Test code: various argument types. */
/* ---------------------------------------------------------------------- */

bool test_argument_type_1(std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_1: results = " << std::any_cast<uintptr_t>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return true;
}

bool test_argument_type_2(std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_2: results = " << std::any_cast<uintptr_t *>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return true;
}

bool test_argument_type_3(std::any& args, std::any& results)
{
    auto& ut = *std::any_cast<UnitTest *>(args);

    ostringstream oss;
    oss << "test_3: results = " << std::any_cast<uintptr_t&>(results);
    CUN_UNITTEST_ECHO(ut, oss.str().c_str());

    return true;
}

void test_argument_type(UnitTest& ut)
{
    CUN_UNITTEST_TITLE(ut, "Test code: Event loop toolbox - various argument types.");
    CUN_UNITTEST_NL(ut);

    EventLoop<EventType>::event_entry entry {
#define ENTRY(type, fn) \
        make_pair(EventType::type, [](void *, std::any& args, std::any& results) { return fn(args, results); })

        // function without a unused context pointer.
        ENTRY(on_test_1, test_argument_type_1),
        ENTRY(on_test_2, test_argument_type_2),
        ENTRY(on_test_3, test_argument_type_3),

#undef ENTRY
    };

    CUN_UNITTEST_EXEC(ut, EventLoop<EventType> el { entry });
    CUN_UNITTEST_EXEC(ut, uintptr_t results = 0xDEADBEEF);
    CUN_UNITTEST_EXEC(ut, auto& results_ref = results);
    CUN_UNITTEST_NL(ut);

    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_1, &ut, results));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_1, &ut, results_ref));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_1, &ut, uintptr_t { 0xFACEFEED }));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_2, &ut, &results));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_2, &ut, &results_ref));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_3, &ut, results));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_3, &ut, results_ref));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_3, &ut, uintptr_t { 0xFACEFEED }));
    CUN_UNITTEST_EVAL(ut, el.send_event(EventType::on_test_1, &ut, std::move(results_ref)));
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
    test_with_ctx_rawptr(ut);
    test_with_ctx_smartptr(ut);
    test_inherited_class(ut);
    test_argument_type(ut);

    return EXIT_SUCCESS;
}
