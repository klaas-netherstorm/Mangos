/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "PlayerbotShamanAI.h"

class PlayerbotAI;

PlayerbotShamanAI::PlayerbotShamanAI(Player* const bot, PlayerbotAI* const ai): PlayerbotClassAI(bot, ai)
{
    InitSpells(ai);
}

PlayerbotShamanAI::~PlayerbotShamanAI() {}

void PlayerbotShamanAI::InitSpells(PlayerbotAI* const ai)
{
    // restoration
    CHAIN_HEAL               = ai->initSpell(CHAIN_HEAL_1);
    HEALING_WAVE             = ai->initSpell(HEALING_WAVE_1);
    LESSER_HEALING_WAVE      = ai->initSpell(LESSER_HEALING_WAVE_1);
    RIPTIDE                  = ai->initSpell(RIPTIDE_1);
    ANCESTRAL_SPIRIT         = ai->initSpell(ANCESTRAL_SPIRIT_1);
    EARTH_SHIELD             = ai->initSpell(EARTH_SHIELD_1);
    WATER_SHIELD             = ai->initSpell(WATER_SHIELD_1);
    EARTHLIVING_WEAPON       = ai->initSpell(EARTHLIVING_WEAPON_1);
    TREMOR_TOTEM             = ai->initSpell(TREMOR_TOTEM_1); // totems
    HEALING_STREAM_TOTEM     = ai->initSpell(HEALING_STREAM_TOTEM_1);
    MANA_SPRING_TOTEM        = ai->initSpell(MANA_SPRING_TOTEM_1);
    MANA_TIDE_TOTEM          = ai->initSpell(MANA_TIDE_TOTEM_1);
    // enhancement
    FOCUSED                  = 0; // Focused what?
    STORMSTRIKE              = ai->initSpell(STORMSTRIKE_1);
    LAVA_LASH                = ai->initSpell(LAVA_LASH_1);
    SHAMANISTIC_RAGE         = ai->initSpell(SHAMANISTIC_RAGE_1);
    BLOODLUST                = ai->initSpell(BLOODLUST_1);
    HEROISM                  = ai->initSpell(HEROISM_1);
    FERAL_SPIRIT             = ai->initSpell(FERAL_SPIRIT_1);
    LIGHTNING_SHIELD         = ai->initSpell(LIGHTNING_SHIELD_1);
    ROCKBITER_WEAPON         = ai->initSpell(ROCKBITER_WEAPON_1);
    FLAMETONGUE_WEAPON       = ai->initSpell(FLAMETONGUE_WEAPON_1);
    FROSTBRAND_WEAPON        = ai->initSpell(FROSTBRAND_WEAPON_1);
    WINDFURY_WEAPON          = ai->initSpell(WINDFURY_WEAPON_1);
    STONESKIN_TOTEM          = ai->initSpell(STONESKIN_TOTEM_1); // totems
    STRENGTH_OF_EARTH_TOTEM  = ai->initSpell(STRENGTH_OF_EARTH_TOTEM_1);
    FROST_RESISTANCE_TOTEM   = ai->initSpell(FROST_RESISTANCE_TOTEM_1);
    FLAMETONGUE_TOTEM        = ai->initSpell(FLAMETONGUE_TOTEM_1);
    FIRE_RESISTANCE_TOTEM    = ai->initSpell(FIRE_RESISTANCE_TOTEM_1);
    GROUNDING_TOTEM          = ai->initSpell(GROUNDING_TOTEM_1);
    NATURE_RESISTANCE_TOTEM  = ai->initSpell(NATURE_RESISTANCE_TOTEM_1);
    WIND_FURY_TOTEM          = ai->initSpell(WINDFURY_TOTEM_1);
    STONESKIN_TOTEM          = ai->initSpell(STONESKIN_TOTEM_1);
    WRATH_OF_AIR_TOTEM       = ai->initSpell(WRATH_OF_AIR_TOTEM_1);
    EARTH_ELEMENTAL_TOTEM    = ai->initSpell(EARTH_ELEMENTAL_TOTEM_1);
    // elemental
    LIGHTNING_BOLT           = ai->initSpell(LIGHTNING_BOLT_1);
    EARTH_SHOCK              = ai->initSpell(EARTH_SHOCK_1);
    FLAME_SHOCK              = ai->initSpell(FLAME_SHOCK_1);
    PURGE                    = ai->initSpell(PURGE_1);
    WIND_SHOCK               = 0; //NPC spell
    FROST_SHOCK              = ai->initSpell(FROST_SHOCK_1);
    CHAIN_LIGHTNING          = ai->initSpell(CHAIN_LIGHTNING_1);
    LAVA_BURST               = ai->initSpell(LAVA_BURST_1);
    HEX                      = ai->initSpell(HEX_1);
    STONECLAW_TOTEM          = ai->initSpell(STONECLAW_TOTEM_1); // totems
    SEARING_TOTEM            = ai->initSpell(SEARING_TOTEM_1);
    FIRE_NOVA_TOTEM          = 0; // NPC only spell, check FIRE_NOVA_1
    MAGMA_TOTEM              = ai->initSpell(MAGMA_TOTEM_1);
    EARTHBIND_TOTEM          = ai->initSpell(EARTHBIND_TOTEM_1);
    TOTEM_OF_WRATH           = ai->initSpell(TOTEM_OF_WRATH_1);
    FIRE_ELEMENTAL_TOTEM     = ai->initSpell(FIRE_ELEMENTAL_TOTEM_1);

    RECENTLY_BANDAGED        = 11196; // first aid check

    // racial
    GIFT_OF_THE_NAARU        = ai->initSpell(GIFT_OF_THE_NAARU_SHAMAN); // draenei
    BLOOD_FURY               = ai->initSpell(BLOOD_FURY_SHAMAN); // orc
    WAR_STOMP                = ai->initSpell(WAR_STOMP_ALL); // tauren
    BERSERKING               = ai->initSpell(BERSERKING_ALL); // troll
}

bool PlayerbotShamanAI::HealTarget(Unit &target, uint8 hp)
{
    Player * m_bot = GetPlayerBot();
    if (!m_bot)
        return false;

    PlayerbotAI* ai = GetAI();
    if (!ai)
        return false;

    Player* pMaster = ai->GetMaster();
    if (!pMaster)
        return false;

    if ((hp < 30)
        && (HEALING_WAVE > 0)
        && (ai->GetManaPercent() >= 32)
        && (ai->CastSpell(HEALING_WAVE, target)))
        return true;

    else if ((hp < 45)
        && (LESSER_HEALING_WAVE > 0)
        && (ai->GetManaPercent() >= 19)
        && (ai->CastSpell(LESSER_HEALING_WAVE, target)))
        return true;

    else if ((hp < 55)
        && (RIPTIDE > 0)
        && (!target.HasAura(RIPTIDE, EFFECT_INDEX_0))
        && (ai->GetManaPercent() >= 21)
        && (ai->CastSpell(RIPTIDE, target)))
        return true;

    else if ((hp < 70)
        && (CHAIN_HEAL > 0)
        && (ai->GetManaPercent() >= 24)
        && (ai->CastSpell(CHAIN_HEAL, target)))
        return true;

    return false;
}

bool PlayerbotShamanAI::DoNextCombatManeuver(Unit *pTarget)
{
    PlayerbotAI* ai = GetAI();
    if (!ai)
        return false;

    Player* pMaster = ai->GetMaster();
    if (!pMaster)
        return false;

    ai->SetMovementOrder(PlayerbotAI::MOVEMENT_FOLLOW, pMaster);

    Player *m_bot = GetPlayerBot();
    Group *m_group = m_bot->GetGroup();

    if ((ai->GetHealthPercent() < 30)
        && (ai->GetManaPercent() >= 32)
        && (ai->CastSpell(HEALING_WAVE)))
        return true;

    if ((ai->GetHealthPercent() < 50)
        && (ai->GetManaPercent() >= 19)
        && (ai->CastSpell(LESSER_HEALING_WAVE)))
        return true;

    if ((ai->GetHealthPercent() < 70)
        && (HealTarget(*m_bot, ai->GetHealthPercent())))
        return true;

    uint32 masterHP = pMaster->GetHealth() * 100 / pMaster->GetMaxHealth();
    if (pMaster->isAlive())
    {
        if ((masterHP < 30)
            && (ai->GetManaPercent() >= 32)
            && (ai->CastSpell(HEALING_WAVE, * (pMaster))))
            return true;

        if ((masterHP < 70)
            && (HealTarget(*pMaster, masterHP)))
            return true;
    }

    if (m_group)
    {
        Group::MemberSlotList const& groupSlot = m_group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *m_groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (!m_groupMember || !m_groupMember->isAlive())
                continue;

            uint32 memberHP = m_groupMember->GetHealth() * 100 / m_groupMember->GetMaxHealth();
            if ((memberHP < 30)
                && (HealTarget(*m_groupMember, memberHP)))
                return true;
        }
    }

    ai->SetInFront(pTarget);

    switch (SpellSequence)
    {
        case SPELL_ENHANCEMENT:

            if ((STRENGTH_OF_EARTH_TOTEM > 0)
                && (LastSpellEnhancement == 1)
                && (!m_bot->HasAura(STRENGTH_OF_EARTH_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 13)
                && (ai->CastSpell(STRENGTH_OF_EARTH_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((STONESKIN_TOTEM > 0)
                && (LastSpellEnhancement == 5)
                && (!m_bot->HasAura(STONESKIN_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(STRENGTH_OF_EARTH_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 13)
                && (ai->CastSpell(STONESKIN_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((FOCUSED > 0)
                && (LastSpellEnhancement == 2)
                && (ai->CastSpell(FOCUSED, *pTarget)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((FROST_RESISTANCE_TOTEM > 0)
                && (LastSpellEnhancement == 10)
                && (!m_bot->HasAura(FROST_RESISTANCE_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(TOTEM_OF_WRATH, EFFECT_INDEX_0))
                && (!m_bot->HasAura(FLAMETONGUE_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 10)
                && (ai->CastSpell(FROST_RESISTANCE_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((FLAMETONGUE_TOTEM > 0)
                && (LastSpellEnhancement == 15)
                && (!m_bot->HasAura(FLAMETONGUE_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(TOTEM_OF_WRATH, EFFECT_INDEX_0))
                && (!m_bot->HasAura(FROST_RESISTANCE_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 14)
                && (ai->CastSpell(FLAMETONGUE_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((FIRE_RESISTANCE_TOTEM > 0)
                && (LastSpellEnhancement == 20)
                && (!m_bot->HasAura(FIRE_RESISTANCE_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(HEALING_STREAM_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(MANA_SPRING_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 10)
                && (ai->CastSpell(FIRE_RESISTANCE_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((GROUNDING_TOTEM > 0)
                && (LastSpellEnhancement == 25)
                && (!m_bot->HasAura(GROUNDING_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(WRATH_OF_AIR_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(WIND_FURY_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 5)
                && (ai->CastSpell(GROUNDING_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((NATURE_RESISTANCE_TOTEM > 0)
                && (LastSpellEnhancement == 30)
                && (!m_bot->HasAura(NATURE_RESISTANCE_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(WRATH_OF_AIR_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(GROUNDING_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(WIND_FURY_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 10)
                && (ai->CastSpell(NATURE_RESISTANCE_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((WIND_FURY_TOTEM > 0)
                && (LastSpellEnhancement == 35)
                && (!m_bot->HasAura(WIND_FURY_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(WRATH_OF_AIR_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(GROUNDING_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 11)
                && (ai->CastSpell(WIND_FURY_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((STORMSTRIKE > 0)
                && (LastSpellEnhancement == 4)
                && (!pTarget->HasAura(STORMSTRIKE, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 8)
                && (ai->CastSpell(STORMSTRIKE, *pTarget)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((LAVA_LASH > 0)
                && (LastSpellEnhancement == 6)
                && (ai->GetManaPercent() >= 4)
                && (ai->CastSpell(LAVA_LASH, *pTarget)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((FERAL_SPIRIT > 0)
                && (LastSpellEnhancement == 7)
                && (ai->GetManaPercent() >= 12)
                && (ai->CastSpell(FERAL_SPIRIT)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((WRATH_OF_AIR_TOTEM > 0)
                && (!m_bot->HasAura(WRATH_OF_AIR_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(GROUNDING_TOTEM, EFFECT_INDEX_0))
                && (LastSpellEnhancement == 40)
                && (ai->CastSpell(WRATH_OF_AIR_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((EARTH_ELEMENTAL_TOTEM > 0)
                && (LastSpellEnhancement == 45)
                && (ai->GetManaPercent() >= 24)
                && (ai->CastSpell(EARTH_ELEMENTAL_TOTEM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((BLOODLUST > 0)
                && (LastSpellEnhancement == 8)
                && (!pMaster->HasAura(BLOODLUST, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 26)
                && (ai->CastSpell(BLOODLUST)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((HEROISM > 0)
                && (LastSpellEnhancement == 10)
                && (!pMaster->HasAura(HEROISM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 26)
                && (ai->CastSpell(HEROISM)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if ((SHAMANISTIC_RAGE > 0)
                && (!m_bot->HasAura(SHAMANISTIC_RAGE, EFFECT_INDEX_0))
                && (LastSpellEnhancement == 11)
                && (ai->CastSpell(SHAMANISTIC_RAGE, *m_bot)))
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement++;
                return true;
            }

            if (LastSpellEnhancement > 50)
            {
                SpellSequence = SPELL_RESTORATION;
                LastSpellEnhancement =1;
                return true;
            }

            LastSpellEnhancement = 0;
            break;

        case SPELL_RESTORATION:

            if ((HEALING_STREAM_TOTEM > 0)
                && (LastSpellRestoration < 3)
                && (ai->GetHealthPercent() < 50)
                && (!m_bot->HasAura(HEALING_STREAM_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(MANA_SPRING_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 4)
                && (ai->CastSpell(HEALING_STREAM_TOTEM)))
            {
                SpellSequence = SPELL_ELEMENTAL;
                LastSpellRestoration++;
                return true;
            }

            if ((MANA_SPRING_TOTEM > 0)
                && (LastSpellRestoration < 4)
                && (!m_bot->HasAura(MANA_SPRING_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(HEALING_STREAM_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 5)
                && (ai->CastSpell(MANA_SPRING_TOTEM)))
            {
                SpellSequence = SPELL_ELEMENTAL;
                LastSpellRestoration++;
                return true;
            }

            if ((MANA_TIDE_TOTEM > 0)
                && (LastSpellRestoration < 5)
                && (ai->GetManaPercent() < 50)
                && (ai->GetManaPercent() >= 3)
                && (ai->CastSpell(MANA_TIDE_TOTEM)))
            {
                SpellSequence = SPELL_ELEMENTAL;
                LastSpellRestoration++;
                return true;
            }

            if (LastSpellRestoration > 6)
            {
                LastSpellRestoration = 0;
                SpellSequence = SPELL_ELEMENTAL;
                return true;
            }

            LastSpellRestoration = 0;
            break;

        case SPELL_ELEMENTAL:

            if ((LIGHTNING_BOLT > 0)
                && (LastSpellElemental == 1)
                && (ai->GetManaPercent() >= 13)
                && (ai->CastSpell(LIGHTNING_BOLT, *pTarget)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((SEARING_TOTEM > 0)
                && (LastSpellElemental == 2)
                && (!pTarget->HasAura(SEARING_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(TOTEM_OF_WRATH, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 9)
                && (ai->CastSpell(SEARING_TOTEM)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((STONECLAW_TOTEM > 0)
                && (ai->GetHealthPercent() < 51)
                && (LastSpellElemental == 3)
                && (!pTarget->HasAura(STONECLAW_TOTEM, EFFECT_INDEX_0))
                && (!pTarget->HasAura(EARTHBIND_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(STRENGTH_OF_EARTH_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 8)
                && (ai->CastSpell(STONECLAW_TOTEM)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((FLAME_SHOCK > 0)
                && (LastSpellElemental == 4)
                && (!pTarget->HasAura(FLAME_SHOCK, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 22)
                && (ai->CastSpell(FLAME_SHOCK, *pTarget)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((LAVA_BURST > 0)
                && (LastSpellElemental == 5)
                && (pTarget->HasAura(FLAME_SHOCK, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 10)
                && (ai->CastSpell(LAVA_BURST, *pTarget)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((MAGMA_TOTEM > 0)
                && (LastSpellElemental == 6)
                && (!m_bot->HasAura(TOTEM_OF_WRATH, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 35)
                && (ai->CastSpell(MAGMA_TOTEM)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((EARTHBIND_TOTEM > 0)
                && (LastSpellElemental == 7)
                && (!pTarget->HasAura(EARTHBIND_TOTEM, EFFECT_INDEX_0))
                && (!m_bot->HasAura(STRENGTH_OF_EARTH_TOTEM, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 5)
                && (ai->CastSpell(EARTHBIND_TOTEM)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((EARTH_SHOCK > 0)
                && (LastSpellElemental == 8)
                && (ai->GetManaPercent() >= 23)
                && (ai->CastSpell(EARTH_SHOCK, *pTarget)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((PURGE > 0)
                && (LastSpellElemental == 9)
                && (ai->GetManaPercent() >= 8)
                && (ai->CastSpell(PURGE, *pTarget)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((WIND_SHOCK > 0)
                && (LastSpellElemental == 10)
                && (ai->GetManaPercent() >= 8)
                && (ai->CastSpell(WIND_SHOCK, *pTarget)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((FIRE_NOVA_TOTEM > 0)
                && (LastSpellElemental == 11)
                && (ai->GetManaPercent() >= 33)
                && (ai->CastSpell(FIRE_NOVA_TOTEM)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((FROST_SHOCK > 0)
                && (LastSpellElemental == 12)
                && (!pTarget->HasAura(FROST_SHOCK, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 23)
                && (ai->CastSpell(FROST_SHOCK, *pTarget)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((CHAIN_LIGHTNING > 0)
                && (LastSpellElemental == 13)
                && (ai->GetManaPercent() >= 33)
                && (ai->CastSpell(CHAIN_LIGHTNING, *pTarget)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((TOTEM_OF_WRATH > 0)
                && (LastSpellElemental == 14)
                && (!m_bot->HasAura(TOTEM_OF_WRATH, EFFECT_INDEX_0))
                && (ai->GetManaPercent() >= 5)
                && (ai->CastSpell(TOTEM_OF_WRATH)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if ((FIRE_ELEMENTAL_TOTEM > 0)
                && (LastSpellElemental == 15)
                && (ai->GetManaPercent() >= 23)
                && (ai->CastSpell(FIRE_ELEMENTAL_TOTEM)))
            {
                SpellSequence = SPELL_ENHANCEMENT;
                LastSpellElemental++;
                return true;
            }

            if (LastSpellElemental > 16)
            {
                LastSpellElemental = 1;
                SpellSequence = SPELL_ENHANCEMENT;
                return true;
            }

            LastSpellElemental = 0;
            SpellSequence = SPELL_ENHANCEMENT;
            break;
    }

    return false;
}

bool PlayerbotShamanAI::DoNonCombatActions()
{
    PlayerbotAI* ai = GetAI();
    if (!ai)
        return false;

    Player* pMaster = ai->GetMaster();
    if (!pMaster)
        return false;

    Player * m_bot = GetPlayerBot();
    if (!m_bot)
        return false;

    SpellSequence = SPELL_ENHANCEMENT;

    if ((EARTH_SHIELD > 0)
        && (!pMaster->HasAura(EARTH_SHIELD, EFFECT_INDEX_0))
        && (ai->CastSpell(EARTH_SHIELD, * (pMaster))))
        return true;

    if ((WATER_SHIELD > 0)
        && (!m_bot->HasAura(WATER_SHIELD, EFFECT_INDEX_0))
        && (!m_bot->HasAura(LIGHTNING_SHIELD, EFFECT_INDEX_0))
        && (ai->CastSpell(WATER_SHIELD, *m_bot)))
        return true;

    else if ((LIGHTNING_SHIELD > 0)
        && (!m_bot->HasAura(LIGHTNING_SHIELD, EFFECT_INDEX_0))
        && (!m_bot->HasAura(WATER_SHIELD, EFFECT_INDEX_0))
        && (ai->CastSpell(LIGHTNING_SHIELD, *m_bot)))
        return true;

    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);

    Item* drinkOrFoodItem = ai->FindDrink();
    Item* bandageItem = ai->FindBandage();

    if (drinkOrFoodItem
        && (ai->GetManaPercent() < 30))
    {
        ai->UseItem(*drinkOrFoodItem);
        ai->SetIgnoreUpdateTime(30);
        return true;
    }

    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);

    drinkOrFoodItem = ai->FindFood();

    if (drinkOrFoodItem
        && (ai->GetHealthPercent() < 30))
    {
        ai->UseItem(*drinkOrFoodItem);
        ai->SetIgnoreUpdateTime(30);
        return true;
    }
    else if (!drinkOrFoodItem
        && bandageItem
        && (!m_bot->HasAura(RECENTLY_BANDAGED, EFFECT_INDEX_0))
        && (ai->GetHealthPercent() < 70))
    {
        ai->UseItem(*bandageItem);
        ai->SetIgnoreUpdateTime(8);
        return true;
    }

    if (pMaster->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = pMaster->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *tPlayer = sObjectMgr.GetPlayer(itr->guid);
            if (!tPlayer || !tPlayer->isAlive())
                continue;

             if (HealTarget(*tPlayer, tPlayer->GetHealth() * 100 / tPlayer->GetMaxHealth()))
                 return true;
        }
    }

    return false;
}
