#pragma once

void new_console();
std::string convert_from_string(Il2CppString* input);
std::string convert_from_string(app::String* input);
app::String* convert_to_string(std::string_view input);
std::string translate_type_name(std::string input);
Il2CppMethodPointer find_method(Il2CppClass* klass, std::string_view returnType, std::string_view methodName, std::string_view paramTypes);
Il2CppMethodPointer get_method(std::string methodSignature);
Il2CppClass* get_class(std::string classSignature);
std::string get_method_description(const MethodInfo* methodInfo);
void output_class_methods(Il2CppClass* klass);
void output_assembly_methods(const Il2CppAssembly* assembly);
bool cctor_finished(Il2CppClass* klass);

class ScopedThreadAttacher {
public:
	ScopedThreadAttacher();
	~ScopedThreadAttacher();

	void detach();
private:
	Il2CppThread* m_AttachedThread;
};
