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

namespace app {
	namespace il2cpp {
		template<typename E>
		class Array {
		public:
			using iterator = decltype(&E::vector[0]);
			constexpr Array(E* arr) : _Ptr(arr) {}
			constexpr size_t size() const {
				if (!_Ptr) return 0;
				if (_Ptr->bounds)
					return _Ptr->bounds->length;
				return _Ptr->max_length;
			}
			constexpr iterator begin() const {
				if (!_Ptr) return nullptr;
				return _Ptr->vector;
			}
			constexpr iterator end() const { return begin() + size(); }
			constexpr auto& operator[](const size_t _Pos) const { return begin()[_Pos]; }
			constexpr E* get() const { return _Ptr; }
		protected:
			E* _Ptr;
		};
	}
}

class ScopedThreadAttacher {
public:
	ScopedThreadAttacher();
	~ScopedThreadAttacher();

	void detach();
private:
	Il2CppThread* m_AttachedThread;
};
