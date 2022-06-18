#include <iostream>
#include <algorithm>
#include <cstring>
#include <string_view>

using simple = std::uint_fast64_t;

class StyleCode{
private:
	std::string m_parameter{};
	static simple s_kratos;
private:
	constexpr bool validate(char **, simple&, simple&)const;
public:
	StyleCode() = default;
public:
	std::string_view snakeCase(simple, char **);
	std::string_view camelCase(simple, char **);	
	std::string_view pascalCase(simple, char **);
	void diag(simple, char **)const;
	void typo()const;
	void help(char **)const;
};

/*********static**********/
simple StyleCode::s_kratos = 0;
/*********static**********/


/************HELPER*****************************/
void StyleCode::diag(simple argc, char **argv)const{
	printf("\n\nargc %ld\n", argc);
	printf("argv\n");
	for(simple i{0}; i < argc; ++i){
		std::cout<<i<<" "<<argv[i]<<'\n';
	}
}

void StyleCode::typo()const{
	printf("Gunakan salah satu argumen berikut : \n");
	printf("-sc --snake_case\n");
	printf("-cs --camelCase\n");
	printf("-ps --PascalCase");
}

void StyleCode::help(char **argv)const{
	printf("BUATAN FARIKUN AZIZ\n");
	printf("\nPenggunaan : %s -[sc,cs,ps] args....n\n",argv[0]);
}

constexpr bool StyleCode::validate(char **argv, simple& i, simple& j)const{
	return ((argv[i][j] >= 'a' and argv[i][j] <= 'z') or (argv[i][j] >= 'A' and argv[i][j] <= 'Z') or (argv[i][j] == ','));
}
/************HELPER*****************************/


/************************METHODs****************************/
std::string_view StyleCode::snakeCase(simple argc, char **argv){
	if(argc == 2){
		help(argv);
	}else{
		for(simple i{2}; i < argc; ++i){
			for(simple j{0}; j<strlen(argv[i]); ++j){
				if(validate(argv,i,j)){
					m_parameter.push_back(argv[i][j]);
				}else{
					m_parameter.push_back(',');
				}
			}
			//tidak perlu beri , pada akhir kata baris terakhir
			if(i < argc - 1){
				m_parameter.push_back(',');	
			}
		}

		const auto len = m_parameter.size();

		for(int i{0}; i < len; ++i){
			if(m_parameter[i] == ','){
				++s_kratos;
			}else{
				s_kratos = 0;
			}

			if(s_kratos == 1){
				m_parameter[i] = '_';
			}else if(s_kratos > 1){
				m_parameter[i] = '\0';
			}
		}	
	}
	
	return m_parameter;
}

std::string_view StyleCode::camelCase(simple argc, char **argv){
	if(argc == 2){
		help(argv);
	}else{
		for(simple i{2}; i < argc; ++i){
			for(simple j{0}; j<strlen(argv[i]); ++j){
				if(validate(argv,i,j)){
					m_parameter.push_back(argv[i][j]);
				}else{
					m_parameter.push_back(',');
				}
			}
			if(i < argc - 1){
				m_parameter.push_back(',');
			}
		}

		const auto len = m_parameter.size();

		for(simple i{0}; i < len; ++i){
			if(m_parameter[i] == ','){
				//ganti karakter selanjutnya dengan upper case
				m_parameter[i+1] = toupper(m_parameter[i+1]);
				//putus/hapus karakter (,) sehingga karakter selanjutnya akan maju
				m_parameter[i] = '\0';
			}
		}
	}

	return m_parameter;
}

std::string_view StyleCode::pascalCase(simple argc, char **argv){
	if(argc == 2){
		help(argv);
	}else{	
		for(simple i{2}; i<argc; ++i){
			for(simple j{0}; j<strlen(argv[i]); ++j){
				if(validate(argv,i,j)){
					m_parameter.push_back(argv[i][j]);
				}else{
					m_parameter.push_back(',');
				}
			}
			if(i < argc - 1){
				m_parameter.push_back(',');
			}
		}

		const auto len = m_parameter.size();
		const char c = toupper(m_parameter[0]);

		for(simple i{1}; i<len; ++i){
			if(m_parameter[i] == ','){
				m_parameter[i+1] = toupper(m_parameter[i+1]);
				m_parameter[i] = '\0';
			}
		}
		m_parameter[0] = c;
	}
	return m_parameter;
}
/************************METHODs****************************/




int main(int argc, char **argv)
{
	StyleCode sc;

	if(argc > 1){
		for(simple i{1}; i<argc; ++i){
			if(strcmp(argv[i],"-sc") == 0){
				std::cout<<sc.snakeCase(argc,argv);
				break;
			}else if(strcmp(argv[i],"-cs") == 0){
				std::cout<<sc.camelCase(argc,argv);
				break;
			}else if(strcmp(argv[i],"-ps") == 0){
				std::cout<<sc.pascalCase(argc,argv);
				break;
			}else if(strcmp(argv[i],"-h") == 0){
				sc.help(argv);
				break;
			}else{
				sc.typo();
				break;
			}
		}	
	}else{
		printf("[%s], -h for help", argv[0]);
	}
	
	printf("\n");
	return 0;
}
