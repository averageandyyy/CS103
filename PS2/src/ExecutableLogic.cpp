#include "ExecutableLogic.h"
#include <stdexcept>

/* ∃x. Cat(x) */
bool isFormulaTrueFor_partI(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    // (void) world;
    // throw std::runtime_error("Not implemented.");
    for (Entity x: world)
    {
        if (Cat(x))
        {
            return true;
        }
    }

    return false;
}

/* ∀x. Robot(x) */
bool isFormulaTrueFor_partII(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    // (void) world;
    // throw std::runtime_error("Not implemented.");
    for (Entity x: world)
    {
        if (!Robot(x))
        {
            return false;
        }
    }

    return true;
}

/* ∃x. (Person(x) ∧ Loves(x, x)) */
bool isFormulaTrueFor_partIII(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    // (void) world;
    // throw std::runtime_error("Not implemented.");
    for (Entity x: world)
    {
        if ((Person(x) && Loves(x,x)))
        {
            return true;
        }
    }

    return false;
}

/* ∀x. (Cat(x) → Loves(x, x)) */
bool isFormulaTrueFor_partIV(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    // (void) world;
    // throw std::runtime_error("Not implemented.");
    for (Entity x: world)
    {
        // If the negation of the implication is true, then implication is false
        // if (Cat(x) && !Loves(x,x))
        // {
        //     return false;
        // }

        // We check the consequent only if the antecedent is true.
        if (!Cat(x))
        {
            continue;
        }
        else
        {
            if (!Loves(x,x))
            {
                return false;
            }
        }
    }

    return true;
}

/*
 * ∀x. (Cat(x) →
 *   ∃y. (Person(y) ∧ ¬Loves(x, y))
 * )
 */
bool isFormulaTrueFor_partV(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    // (void) world;
    // throw std::runtime_error("Not implemented.");

    for (Entity x: world)
    {
        if (!Cat(x))
        {
            continue;
        }
        else
        {
            // If x is a cat, check for a y that is person and loves.
            bool found_y = false;
            for (Entity y: world)
            {
                // once that y is found, we stop searching
                if (Person(y) && !Loves(x,y))
                {
                    found_y=true;
                    break;
                }
            }
            // Contract is violated when x is a cat, but no relevant y can be found
            if (!found_y)
            {
                return false;
            }
        }
    }

    return true;
}

/*
 * ∃x. (Robot(x) ↔
 *   ∀y. Loves(x, y)
 * )
 *
 * Robot(x) -> Loves(x,y
 * Loves(x,y) -> Robot(x)
 */

// Helper functions
bool robotImpliesLove(Entity x, std::set<Entity> world)
{
    if (!Robot(x))
    {
        return true;
    }

    for (Entity y: world)
    {
        if (!(Loves(x, y)))
        {
            return false;
        }
    }

    return true;
}

bool lovesImplieRobot(Entity x, std::set<Entity> world)
{
    bool lovesAll = true;
    for (Entity y: world)
    {
        if (!Loves(x, y))
        {
            lovesAll = false;
            break;
        }
    }

    if (!lovesAll)
    {
        return true;
    }

    return Robot(x);
}

bool isFormulaTrueFor_partVI(std::set<Entity> world) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    // (void) world;
    // throw std::runtime_error("Not implemented.");
    for (Entity x: world)
    {
        if (robotImpliesLove(x, world) && lovesImplieRobot(x, world))
        {
            return true;
        }
    }

    return false;
}
