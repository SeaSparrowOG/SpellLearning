#pragma once

namespace Hooks {
    //Hook triggers when reading a book from a container, but not the player's inventory.
    struct ReadBookContainer {

        static bool thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2);

        static void Install();

        static inline REL::Relocation<decltype(thunk)> func;
    };

    //Hook triggers when reading a book from the player's inventory.
    struct ReadBookInventory {

        static bool thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2);

        static void Install();

        static inline REL::Relocation<decltype(thunk)> func;
    };

    //Hook triggers when reading a book from the overworld.
    struct ReadBookReference {

        static bool thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2);

        static void Install();

        static inline REL::Relocation<decltype(thunk)> func;
    };

    //Hook triggers when reading a book from the overworld.
    struct SpellAdded {

        static bool thunk(RE::Actor* a_learner, RE::SpellItem* a_spell);

        static void Install();

        static inline REL::Relocation<decltype(thunk)> func;
    };

	void Install();
}