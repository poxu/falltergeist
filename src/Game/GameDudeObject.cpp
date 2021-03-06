/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// C++ standard includes
#include <cmath>

// Falltergeist includes
#include "../Game/GameDudeObject.h"

// Third party includes

namespace Falltergeist
{

GameDudeObject::GameDudeObject() : GameCritterObject()
{
    _type = TYPE_DUDE;
}

GameDudeObject::~GameDudeObject()
{
}

void GameDudeObject::loadFromGCDFile(libfalltergeist::GcdFileType* gcd)
{
    for (unsigned int i = 0; i <= 6; i++)
    {
        setStat(i, gcd->stat(i));
        setStatBonus(i, gcd->statBonus(i));
    }

    _statsPoints = gcd->characterPoints();
    _name = gcd->name();
    _age = gcd->age();

    _hitPointsMax = gcd->hitPoints() + gcd->hitPointsBonus();

    if (gcd->firstTrait() >= 0) setTrait(gcd->firstTrait(), 1);
    if (gcd->secondTrait() >= 0) setTrait(gcd->secondTrait(), 1);

    if (gcd->firstTaggedSkill() >= 0)
    {
        setSkill(gcd->firstTaggedSkill(), 1);
        _skillsPoints--;
    }
    if (gcd->secondTaggedSkill() >= 0)
    {
        setSkill(gcd->secondTaggedSkill(), 1);
        _skillsPoints--;
    }
    if (gcd->thirdTaggedSkill() >= 0)
    {
        setSkill(gcd->thirdTaggedSkill(), 1);
        _skillsPoints--;
    }

    this->setGender(gcd->gender());
    
}

int GameDudeObject::experience()
{
    return _experience;
}

void GameDudeObject::setExperience(int value)
{
    _experience = value;
}

std::string GameDudeObject::biography()
{
    return _biography;
}

void GameDudeObject::setBiography(std::string value)
{
    _biography = value;
}

int GameDudeObject::age()
{
    return _age;
}

void GameDudeObject::setAge(int value)
{
    _age = value;
}

int GameDudeObject::statsPoints()
{
    return _statsPoints;
}

void GameDudeObject::setStatsPoints(int value)
{
    _statsPoints = value;
}

int GameDudeObject::skillsPoints()
{
    return _skillsPoints;
}

void GameDudeObject::setSkillsPoints(int value)
{
    _skillsPoints = value;
}

int GameDudeObject::hitPointsMax()
{
    int value = 15;
    value += statTotal(STATS_ENDURANCE) * 2;
    value += statTotal(STATS_STRENGTH);
    value += (2 + ceil(statTotal(STATS_ENDURANCE)/2))*(level() - 1);
    return value;
}

int GameDudeObject::level()
{
    return _level;
}

void GameDudeObject::setLevel(int value)
{
    _level = value;
}

int GameDudeObject::armorClass()
{
    unsigned int value = 0;
    if (!trait(TRAITS_KAMIKAZE))
    {
        value += statTotal(STATS_AGILITY) > 10 ? 10 : statTotal(STATS_AGILITY);
    }
    return value;

}

int GameDudeObject::actionPoints()
{
    unsigned int value = 0;
    value += 5 + ceil(statTotal(STATS_AGILITY)/2);
    if (trait(TRAITS_BRUISER))
    {
        value -= 2;
    }
    return value;
}

int GameDudeObject::carryWeight()
{
    unsigned int value = 0;
    unsigned int st = statTotal(STATS_STRENGTH);

    if (trait(TRAITS_SMALL_FRAME))
    {
        value += 25 + 15*(st > 10 ? 10 : st);
        if (trait(TRAITS_GIFTED) && st <= 10)
        {
            value += 10;
        }
    }
    else
    {
        value += 25 + 25*(st > 10 ? 10 : st);
    }
    return value;
}

int GameDudeObject::meleeDamage()
{
    unsigned int value = 0;
    unsigned int st = statTotal(STATS_STRENGTH);
    if (st > 10) st = 10;
    value += st > 5 ? st - 5 : 1;
    if (trait(TRAITS_HEAVY_HANDED))
    {
        value += 4;
    }
    return value;
}

int GameDudeObject::damageResistance()
{
    return 0;
}

int GameDudeObject::radiationResistance()
{
    return 0;
}

int GameDudeObject::poisonResistance()
{
    int value = 0;
    if (!trait(TRAITS_FAST_METABOLISM))
    {
        value += 5*statTotal(STATS_ENDURANCE);
    }
    return value;
}

int GameDudeObject::sequence()
{
    unsigned int value = 0;
    unsigned int pe = statTotal(STATS_PERCEPTION);
    value += 2*(pe > 10 ? 10 : pe);
    if (trait(TRAITS_KAMIKAZE))
    {
        value += 5;
    }
    return value;
}

int GameDudeObject::healingRate()
{
    unsigned int value = 0;
    unsigned int en = statTotal(STATS_ENDURANCE);
    value += ceil((en > 10 ? 10 : en) / 3);
    if (value == 0) value = 1;

    if (trait(TRAITS_FAST_METABOLISM))
    {
        value += 2;
    }
    return value;
}

int GameDudeObject::criticalChance()
{
    unsigned int value = 0;
    unsigned int lk = statTotal(STATS_LUCK);
    value += lk > 10 ? 10 : lk;
    if (trait(TRAITS_FINESSE))
    {
        value += 10;
    }
    return value;
}

}
