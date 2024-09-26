#include "hooks.h"

#include "xbyak/xbyak.h"

namespace Hooks {
	bool ReadBook::thunk(RE::TESObjectBOOK* a_book, RE::SpellItem* a_spell)
	{
		_loggerDebug("Reference hook");
		if (a_book && a_book->TeachesSpell()) {
			auto* bookSpell = a_book->GetSpell();
			_loggerDebug("Player attempted to learn {}", _debugEDID(bookSpell));
		}
		else if (a_book && a_book->TeachesSkill()) {
			_loggerDebug("Player attempted to level {}", a_book->GetSkill());
		}
	}

	void ReadBook::Install()
	{
		struct Patch : public Xbyak::CodeGenerator
		{
			Patch(std::uintptr_t a_funcAddr)
			{
				Xbyak::Label hookAddr;
				L(hookAddr);

				mov(rcx, r15);
				mov(rax, a_funcAddr);
				call(rax);
				mov(rsi, 0);

				jmp(hookAddr.getAddress() + 0x6E);
			}
		};

		std::uintptr_t hookAddr = REL::ID(17842).address() + 0x11D;
		auto pattern = REL::make_pattern<"48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ??">();
		if (!pattern.match(hookAddr)) {
			SKSE::stl::report_and_fail("Binary did not match expected, failed to install"sv);
		}

		std::uintptr_t funcAddr = reinterpret_cast<std::uintptr_t>(thunk);
		Patch patch{ funcAddr };
		patch.ready();

		if (patch.getSize() > 0x56) {
			SKSE::stl::report_and_fail("Patch was too large, failed to install"sv);
		}

		REL::safe_fill(hookAddr, REL::NOP, 0x56);
		REL::safe_write(hookAddr, patch.getCode(), patch.getSize());
	}

	void Install()
	{
		ReadBook::Install();
		_loggerInfo("Finished installing hooks.");
	}
}