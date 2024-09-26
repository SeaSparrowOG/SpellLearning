#pragma once

namespace Utils {
	template <typename T>
	T* ParseForm(const std::string& a_identifier) {
		if (const auto splitID = clib_util::string::split(a_identifier, "|"); splitID.size() == 2) {
			if (!clib_util::string::is_only_hex(splitID[1])) return nullptr;
			const auto  formID = clib_util::string::to_num<RE::FormID>(splitID[1], true);

			const auto& modName = splitID[0];
			if (!RE::TESDataHandler::GetSingleton()->LookupModByName(modName)) return nullptr;

			return RE::TESDataHandler::GetSingleton()->LookupForm<T>(formID, modName);
		}
		return RE::TESForm::LookupByEditorID<T>(a_identifier);
	}
}