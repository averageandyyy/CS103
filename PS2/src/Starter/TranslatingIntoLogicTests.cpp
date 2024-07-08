#include "../ExecutableLogic.h"
#include "WorldDecompressor.h"
#include "Logic/FOLParser.h"
#include "Logic/FOLExpressionBuilder.h"
#include "Logic/WorldParser.h"
#include "Logic/RealEntity.h"
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
    }

    /* Convenience wrapper for the above function given an FOL formula. */
    template <typename Examples, typename Single = typename Examples::value_type>
    pair<Result, Single> passesTests(shared_ptr<FOL::BooleanExpression> expr,
                                     const Examples& negative,
                                     const Examples& positive) {
        return passesTests([&](const World& world) { return expr->evaluate(world); },
                           negative, positive);
    }

    template <typename Examples>
    void checkPassesTests(shared_ptr<FOL::BooleanExpression> expr,
                          const Examples& negative,
                          const Examples& positive) {
        auto result = passesTests(expr, negative, positive);
        if (result.first != Result::CORRECT) {
            ostringstream builder;
            builder << "Answer incorrectly evaluates to "
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

    shared_ptr<FOL::BooleanExpression> loadFormula(const string& section) {
        try {
            return FOL::buildExpressionFor(FOL::parse(FOL::scan(*parseFile("res/TranslatingIntoLogic.fol").at(section))), entityBuildContext());
        } catch (const out_of_range &) {
            SHOW_ERROR("Error loading your answer: Section " + section + " not found.");
        } catch (const exception& e) {
            SHOW_ERROR("Error loading your answer: " + to_string(e.what()));
        }
    }
}

PROVIDED_TEST("Part (i)") {
    auto examples = examplesFrom("TranslationTest1.worlds");
    auto formula = loadFormula("[Part (i)]");
    checkPassesTests(formula, examples.first, examples.second);
}

PROVIDED_TEST("Part (ii)") {
    auto examples = examplesFrom("TranslationTest2.worlds");
    auto formula = loadFormula("[Part (ii)]");
    checkPassesTests(formula, examples.first, examples.second);
}

PROVIDED_TEST("Part (iii)") {
    auto examples = examplesFrom("TranslationTest3.worlds");
    auto formula = loadFormula("[Part (iii)]");
    checkPassesTests(formula, examples.first, examples.second);
}

PROVIDED_TEST("Part (iv)") {
    auto examples = examplesFrom("TranslationTest4.worlds");
    auto formula = loadFormula("[Part (iv)]");
    checkPassesTests(formula, examples.first, examples.second);
}

PROVIDED_TEST("Part (v)") {
    auto examples = examplesFrom("TranslationTest5.worlds");
    auto formula = loadFormula("[Part (v)]");
    checkPassesTests(formula, examples.first, examples.second);
}

PROVIDED_TEST("Part (vi)") {
    auto examples = examplesFrom("TranslationTest6.worlds");
    auto formula = loadFormula("[Part (vi)]");
    checkPassesTests(formula, examples.first, examples.second);
}
