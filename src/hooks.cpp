#include "hooks.h"

#include "xbyak/xbyak.h"

namespace {

    bool inline EvaluateBook(RE::TESObjectBOOK* a_book, RE::PlayerCharacter* a_player) {
        _loggerDebug("  Evaluating book: {}", _debugEDID(a_book));
        if (!a_book || !a_player) return false;

        if (a_book->TeachesSpell()) {
            auto* bookSpell = a_book->GetSpell();
            _loggerDebug("    >Teaches spell: {}", _debugEDID(bookSpell));
            if (a_player->HasSpell(bookSpell)) return false;
        }
        else if (a_book->TeachesSkill()) {
            auto bookSkill = a_book->GetSkill();
            if (bookSkill == RE::ActorValue::kIllusion) {

            }
            else if (bookSkill == RE::ActorValue::kConjuration) {

            }
            else if (bookSkill == RE::ActorValue::kDestruction) {

            }
            else if (bookSkill == RE::ActorValue::kRestoration) {

            }
            else if (bookSkill == RE::ActorValue::kAlteration) {

            }
            _loggerDebug("  >Levels skill: {}", bookSkill);

            return false;
        }
        else {
            return false;
        }
        return true;
    }
}

namespace Hooks {

    bool ReadBookReference::thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2)
    {
        _loggerInfo("Hook: Read from world");
        if (EvaluateBook(a1, a2)) {
            return true;
        }
        else {
            return func(a1, a2);
        }
    }

    void ReadBookReference::Install()
    {
        REL::Relocation<std::uintptr_t> target{ REL::ID(51053), 0x231 };
        stl::write_thunk_call<ReadBookReference>(target.address());
    }

    bool ReadBookInventory::thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2)
    {
        _loggerInfo("Hook: Read from Inventory");
        if (EvaluateBook(a1, a2)) {
            return true;
        }
        else {
            return func(a1, a2);
        }
    }

    void ReadBookInventory::Install()
    {
        REL::Relocation<std::uintptr_t> target{ REL::ID(51870), 0x1A7 };
        stl::write_thunk_call<ReadBookInventory>(target.address());
    }

    bool ReadBookContainer::thunk(RE::TESObjectBOOK* a1, RE::PlayerCharacter* a2)
    {
        _loggerInfo("Hook: Read from container");
        if (EvaluateBook(a1, a2)) {
            return true;
        }
        else {
            return func(a1, a2);
        }
    }

    void ReadBookContainer::Install()
    {
        REL::Relocation<std::uintptr_t> target{ REL::ID(51149), 0x18E };
        stl::write_thunk_call<ReadBookContainer>(target.address());
    }

	void Install()
	{
        ReadBookReference::Install();
        ReadBookInventory::Install();
        ReadBookContainer::Install();
		_loggerInfo("Finished installing hooks.");
	}
}