#pragma once

namespace Hooks {
    struct ReadBookContainer {

        static bool thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2);

        static void Install();

        static inline REL::Relocation<decltype(thunk)> func;
    };

    struct ReadBookInventory {

        static bool thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2);

        static void Install();

        static inline REL::Relocation<decltype(thunk)> func;
    };

    struct ReadBookReference {

        static bool thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2);

        static void Install();

        static inline REL::Relocation<decltype(thunk)> func;
    };

	void Install();
}