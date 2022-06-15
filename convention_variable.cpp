#include <iostream>
#include <algorithm>
#include <cstring>
#include <string_view>

//data hanya berkisar 0-255, jika menggunakan int saya rasa pemborosan walaupun sistem bisa mengaturnya sendiri
using simple = std::uint_fast8_t;

class StyleCode{
private:
	std::string m_parameter{};
public:
	StyleCode() = default;
public:
	std::string_view snake_case(simple, char **);
	std::string_view camel_case(simple, char **);	
	std::string_view pascal_case(simple, char **);
	void diag(simple, char **)const;
	void typo()const;
	void help(char **)const;
};

/************HELPER*****************************/
void StyleCode::diag(simple argc, char **argv)const{
	printf("\n\nargc %d\n", argc);
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
/************HELPER*****************************/


/************************METHODs****************************/
std::string_view StyleCode::snake_case(simple argc, char **argv){
	//[0] -> program name,[1] -> first argument for operation
	if(argc == 2){
		help(argv);
	}else{
		//snake case -> snake_case
		//char ** actually 2d array, so yes indeed need 2 loops to iterate the row (i) and it's content (j), same for the rest
		for(simple i{2}; i < argc; ++i){
			for(simple j{0}; j<strlen(argv[i]); ++j){
				m_parameter.push_back(argv[i][j]);
			}
			//tidak perlu beri , pada akhir kata baris terakhir
			if(i < argc - 1){
				m_parameter.push_back(',');	
			}
		}

		//ganti , dengan _
		std::for_each(m_parameter.begin(), m_parameter.end(),[](char& c){
			if(c == ','){
				c = '_';
			}
		});	
	}
	
	return m_parameter;
}

std::string_view StyleCode::camel_case(simple argc, char **argv){
	if(argc == 2){
		help(argv);
	}else{
		//camel case variable -> camelCaseVariable
		for(simple i{2}; i < argc; ++i){
			for(simple j{0}; j<strlen(argv[i]); ++j){
				m_parameter.push_back(argv[i][j]);
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

std::string_view StyleCode::pascal_case(simple argc, char **argv){
	if(argc == 2){
		help(argv);
	}else{	
		//pascal case -> PascalCase
		for(simple i{2}; i<argc; ++i){
			for(simple j{0}; j<strlen(argv[i]); ++j){
				m_parameter.push_back(argv[i][j]);
			}
			if(i < argc - 1){
				m_parameter.push_back(',');
			}
		}

		const auto len = m_parameter.size();
		char c = toupper(m_parameter[0]);

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
				std::cout<<sc.snake_case(argc,argv);
				break;
			}else if(strcmp(argv[i],"-cs") == 0){
				std::cout<<sc.camel_case(argc,argv);
				break;
			}else if(strcmp(argv[i],"-ps") == 0){
				std::cout<<sc.pascal_case(argc,argv);
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