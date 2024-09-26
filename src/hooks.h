#pragma once

namespace Hooks {
    struct ReadBook {

        static bool thunk(RE::TESObjectBOOK* a_book, RE::SpellItem* a_spell);

        static void Install();

        static inline REL::Relocation<decltype(thunk)> _ReadBookReference;
        static inline REL::Relocation<decltype(thunk)> _ReadBookInventory;
        static inline REL::Relocation<decltype(thunk)> _ReadBookContainer;
    };

	void Install();
}