#include "class.hpp"
#include <iostream>
#include <vector>
#include <map>

extern std::map<char,Class> _class_table;
extern std::vector<std::map<char,Variable> > _stack;
extern int _sp;

bool Class::typecheck() {
    
    for(auto d : _cd)
        if(!d->typecheck(_class_local,  _function_local))
            return false;
    
    return true;
}

std::string Class::get_type(char d) {
    
    for(auto i : _cd)
        if(i->get_name() == d)
            return i->get_type();

    return "false";
}

bool Variable_declaration::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local){
    
    return true;
}

bool Function_declaration::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local){
    
    int type_error = 0;
    for(Statement *i : _body)
        if(!i->typecheck(class_local, function_local, _name))
            type_error = 1;
        
    if(!type_error)    
        return true;
    else
        return false;
}

bool Expression_statement::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name) {
    
    if(_e->typecheck(class_local,function_local,name) == "false") {
        
        std::cout << _e->print() << std::endl;
        for(auto string : _e->get_errors())
            std::cout << "> " << string << std::endl;
        return false;
    }
    else
        return true;
}

bool Assignment::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    
    if(!function_local[name].count(_name) && !class_local.count(_name)) {
        
        std::cout << "Greska pri pokusaju dodele: " << std::endl;
        std::cout <<  _name << " = " << _rhs->print() << ";" << std::endl;
        std::cout << "> Ne postoji promenljiva " << std::string(1,_name) << "." << std::endl;
        return false;
    }
    
    
    std::string rhs_typecheck = _rhs->typecheck(class_local,function_local,name);
    if(function_local[name].count(_name)){
        if((function_local[name][_name].get_type() == "double" &&  rhs_typecheck=="int") || 
            (function_local[name][_name].get_type() == "int" &&  rhs_typecheck=="double"))
            return true;
        if(function_local[name][_name].get_type() == rhs_typecheck)
            return true;
        else {
        
            std::cout << "Greska pri pokusaju dodele: " << std::endl;
            std::cout <<  _name << " = " << _rhs->print() << ";" << std::endl;
            for(auto string : _rhs->get_errors())
                std::cout << "> " << string << std::endl;
            return false;
            
        }
    }
    else {
        
        if((class_local[_name].get_type() == "double" &&  rhs_typecheck=="int") || 
            (class_local[_name].get_type() == "int" &&  rhs_typecheck=="double"))
            return true;
        if(class_local[_name].get_type() == rhs_typecheck)
            return true;
        else {
        
            std::cout << "Greska pri pokusaju dodele: " << std::endl;
            std::cout <<  _name << " = " << _rhs->print() << ";" << std::endl;
            for(auto string : _rhs->get_errors())
                std::cout << "> " << string << std::endl;
            return false;
        
        }
        
    }
}

bool Declaration::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    return true;
}

bool Declaration_and_assigment::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    std::string rhs_typecheck = _rhs->typecheck(class_local,function_local,name);
    
    if(_type ==rhs_typecheck)
        return true;
    
    if ((_type == "double" && rhs_typecheck == "int") || (_type == "int" && rhs_typecheck == "double"))
        return true;
    
    std::cout << "Greska pri pokusaju deklaracije i dodele: " << std::endl;
    std::cout <<  _type << " " << _name << " = " << _rhs->print() << ";" << std::endl;
    std::cout << "> Nekompatibilni tipovi." << std::endl;
    for(auto string : _rhs->get_errors())
            std::cout << "> " << string << std::endl;
    
    return false;
}

std::string Variable::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    return _type;
    
}

std::string Constant::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    return _type;
}

std::string Addition::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    std::string lhs_type = _lhs->typecheck(class_local,function_local,name);
    std::string rhs_type = _rhs->typecheck(class_local,function_local,name);
    
    if(lhs_type==rhs_type)
        return lhs_type;
    
    if((lhs_type=="double" && rhs_type=="int") || (lhs_type=="int" && rhs_type=="double"))
        return "double";
    else{
        _errors.push_back("Nekompatibilni tipovi");
        for(auto string : _lhs->get_errors())
            _errors.push_back(string);
        for(auto string : _rhs->get_errors())
            _errors.push_back(string);
        return "false";
    }
}



std::string Method_call::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    if(!class_local.count(_varname) && !function_local[name].count(_varname)){
        
        _errors.push_back("Metod " + std::string(1,_varname) + " nije deklarisan.");
        return "false";
    }
    
    if(!_class_table.count(class_local[_varname].get_type()[0])){
        
        _errors.push_back("Ne postoji klasa " + std::string(1,class_local[_varname].get_type()[0]) + ".");
        return "false";
    }
    
    if(class_local.count(_varname)){
        for(auto decl : _class_table[class_local[_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
            
            _errors.push_back("Metod " + std::string(1,_varname) + "." + std::string(1,_name) + " je private.");
            return "false";
        }
    } 
    else {
        
        for(auto decl : _class_table[function_local[name][_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
            
            _errors.push_back("Metod " + std::string(1,_varname) + "." + std::string(1,_name) + " je private.");
            return "false";
        }
    }

    if(class_local.count(_varname)){
      
        bool exists = false;
        for(auto decl : _class_table[class_local[_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name) 
                exists = true;
        
        if(!exists){
            
            _errors.push_back("Metod " + print() + " ne postoji.");
            return "false";
            
        }
        
        return _class_table[class_local[_varname].get_type()[0]].get_type(_name);   
   
    }
    else {
        
        bool exists = false;
        for(auto decl : _class_table[function_local[name][_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name) 
                exists = true;
        
        if(!exists){
            
            _errors.push_back("Metod " + print() + " ne postoji.");
            return "false";
            
        }
        
        return _class_table[function_local[name][_varname].get_type()[0]].get_type(_name); 
    }
    
}

std::string Attribute_call::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
     
    if(!class_local.count(_varname) && !function_local[name].count(_varname)){
        
        _errors.push_back("Promenljiva " + std::string(1,_varname) + " nije deklarisana.");
        return "false";
    }
    
    if(!_class_table.count(class_local[_varname].get_type()[0])){
        
        _errors.push_back("Ne postoji klasa " + std::string(1,class_local[_varname].get_type()[0]) + ".");
        return "false";
    }
    
    if(class_local.count(_varname)){
        for(auto decl : _class_table[class_local[_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
            
            _errors.push_back("Atribut " + std::string(1,_varname) + "." + std::string(1,_name) + " je private.");
            return "false";
        }
    } 
    else {
        
        for(auto decl : _class_table[function_local[name][_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name && decl->get_encapsulation() == "private"){
            
            _errors.push_back("Atribut " + std::string(1,_varname) + "." + std::string(1,_name) + " je private.");
            return "false";
        }
    }

    if(class_local.count(_varname)){
      
        bool exists = false;
        for(auto decl : _class_table[class_local[_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name) 
                exists = true;
        
        if(!exists){
            
            _errors.push_back("Atribut " + print() + " ne postoji.");
            return "false";
            
        }
        
        return _class_table[class_local[_varname].get_type()[0]].get_type(_name);   
   
    }
    else {
        
        bool exists = false;
        for(auto decl : _class_table[function_local[name][_varname].get_type()[0]].get_declarations())
            if(decl->get_name() == _name) 
                exists = true;
        
        if(!exists){
            
            _errors.push_back("Atribut " + print() + " ne postoji.");
            return "false";
            
        }
        
        return _class_table[function_local[name][_varname].get_type()[0]].get_type(_name); 
    }
}

std::string Function_call::typecheck(std::map<char,Variable> class_local, std::map<char, std::map<char, Variable> > function_local, char name){
    
    if(!class_local.count(_name)){
        
        _errors.push_back("Funkcija " + std::string(1,_name) + " nije deklarisana.");
        return "false";
    }
    else
        return class_local[_name].typecheck(class_local,function_local,name);
} 

/* ---------------------------------- PRINT ----------------------------- */

std::string Variable::print(){
    
    return std::string(1,_name);
} 

std::string Constant::print(){
    
    return _value;
} 

std::string Addition::print(){
    
    return " " + _lhs->print() + " + " + _rhs->print();
}

std::string Method_call::print(){
    
    return std::string(1,_varname) + "." + std::string(1,_name) + "()";
}

std::string Attribute_call::print(){
    
    return std::string(1,_varname) + "." + std::string(1,_name);
}

std::string Function_call::print(){
    
    return std::string(1,_name) + "()";
}




