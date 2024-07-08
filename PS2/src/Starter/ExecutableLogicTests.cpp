#include "../ExecutableLogic.h"
#include "WorldDecompressor.h"
#include "Logic/FOLParser.h"
#include "Logic/FOLExpressionBuilder.h"
#include "Logic/WorldParser.h"
#include "FileParser/FileParser.h"
#include "GUI/SimpleTest.h"
#include "Grabbag/GrabbagTester.h"
using namespace std;

namespace {
    enum class Result {
        CORRECT,
        INCORRECTLY_FALSE,
        INCORRECTLY_TRUE
    };

    string toString(Result r) {
        if (r == Result::CORRECT) return "correct";
        if (r == Result::INCORRECTLY_FALSE) return "false";
        return "true";
    }

    /* Given a collection of positive and negative examples, does the given function evaluate
         * to true for all the positive examples and false for all the negative examples?
         */
    template <typename Examples, typename Single = typename Examples::value_type>
    pair<Result, Single> passesTests(function<bool(World)> predicate,
                                     const Examples& negative,
                                     const Examples& positive) {
        try {
            for (const auto& example: negative) {
                if (predicate(example)) {
                    return make_pair(Result::INCORRECTLY_TRUE, example);
                }
            }
            for (const auto& example: positive) {
                if (!predicate(example)) {
                    return make_pair(Result::INCORRECTLY_FALSE, example);
                }
            }
            return make_pair(Result::CORRECT, Single());
        }  catch (const exception& e) {
            SHOW_ERROR("Function reported an error: " + string(e.what()));
        }
    }

    template <typename Examples>
    void checkPassesTests(function<bool(World)> predicate,
                          const Examples& negative,
                          const Examples& positive) {
        auto result = passesTests(predicate, negative, positive);
        if (result.first != Result::CORRECT) {
            ostringstream builder;
            builder << "Function incorrectly evaluates to "
                    << toString(result.first) << " on the following world:" << endl;
            builder << "[begin world description]" << endl;
            builder << result.second;
            builder << "[end world description]" << endl;

            SHOW_ERROR(builder.str());
        }
    }

    /* Given a filename, returns all the negative and positive examples from that file,
     * respectively.
     */
    pair<vector<World>, vector<World>> examplesFrom(const string& filename) {
        pair<vector<World>, vector<World>> result;
        runPrivateTest(filename, [&](istream& in) {
            result = Decompressor::parse(in);
        });
        return result;
    }
}

PROVIDED_TEST("Part (i)") {
    auto examples = examplesFrom("ExecutableLogicTest1.worlds");
    checkPassesTests(isFormulaTrueFor_partI, examples.first, examples.second);
}

PROVIDED_TEST("Part (ii)") {
    auto examples = examplesFrom("ExecutableLogicTest2.worlds");
    checkPassesTests(isFormulaTrueFor_partII, examples.first, examples.second);
}

PROVIDED_TEST("Part (iii)") {
    auto examples = examplesFrom("ExecutableLogicTest3.worlds");
    checkPassesTests(isFormulaTrueFor_partIII, examples.first, examples.second);
}

PROVIDED_TEST("Part (iv)") {
    auto examples = examplesFrom("ExecutableLogicTest4.worlds");
    checkPassesTests(isFormulaTrueFor_partIV, examples.first, examples.second);
}

PROVIDED_TEST("Part (v)") {
    auto examples = examplesFrom("ExecutableLogicTest5.worlds");
    checkPassesTests(isFormulaTrueFor_partV, examples.first, examples.second);
}

PROVIDED_TEST("Part (vi)") {
    auto examples = examplesFrom("ExecutableLogicTest6.worlds");
    checkPassesTests(isFormulaTrueFor_partVI, examples.first, examples.second);
}
