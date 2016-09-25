%option noyywrap
%option nounput
%option noinput

%{
#include "class.hpp"
#include "parser.tab.hpp"
%}

%%

class { 

    return class_token;
}

end {

    return end_token;
}
public {

    yylval.s = new std::string(yytext);
    return public_token;
}

private {
    
    yylval.s = new std::string(yytext);
    return private_token;
}

int {
    
    yylval.s = new std::string(yytext);
    return int_token;
}

double {

    yylval.s = new std::string(yytext);
    return double_token;
}

void {

    yylval.s = new std::string(yytext);
    return void_token;
}

string {

    yylval.s = new std::string(yytext);
    return string_token;
}

[A-Z] {

    yylval.c = *yytext;
    return idclass_token;
}

[a-z] {

    yylval.c = *yytext;
    return id_token;
}

[0-9]+\.[0-9]+  {

    return const_double_token;
}

[0-9]+  {

    return const_int_token;
}

\"[a-z\n]+\"  {

    return const_string_token;
}

[,;{}=\(\)+.] {

    return *yytext;
}

[\n\t ] {
}

%%