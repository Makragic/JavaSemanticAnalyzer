#include "class.hpp"
#include <iostream>
#include <vector>
#include <map>

extern std::map<char,Class> _class_table;
extern std::map<char,Variable> _local_table;

bool Class::typecheck() {
    
    for(auto d : _cd)
        if(!d->typecheck())
            return false;
    
    return true;
}

std::string Class::get_type(char d) {
    
    for(auto i : _cd)
        if(i->get_name() == d)
            return i->get_type();

    return "false";
    
}

bool Variable_declaration::typecheck(){
    
    return true;
}

bool Function_declaration::typecheck(){
    
    for(Statement *i : _body)
        if(!i->typecheck()) 
            return false;
        
        
    return true;
}

bool Expression_statement::typecheck() {
    
    if(_e->typecheck() == "false") {
        return false;
    }
    else
        return true;
}

bool Assignment::typecheck(){
    
    
    if(!_local_table.count(_name))
        return false;
    
    if((_local_table[_name].get_type() == "double" &&  _rhs->typecheck()=="int") || 
        (_local_table[_name].get_type() == "int" &&  _rhs->typecheck()=="double"))
        return true;
    
    if(_local_table[_name].get_type() == _rhs->typecheck())
        return true;
    else
        return false;
}

bool Declaration::typecheck(){
    
    return true;
}

bool Declaration_and_assigment::typecheck(){
    
    if(_type ==_rhs->typecheck())
        return true;
    
    if ((_type == "double" && _rhs->typecheck()=="int") || (_type == "int" && _rhs->typecheck()=="double"))
        return true;
     
    return false;
}

std::string Variable::typecheck(){
    
    return _type;
    
}

std::string Constant::typecheck(){
    
    return _type;
}

std::string Addition::typecheck(){
    
    std::string lhs_type = _lhs->typecheck();
    std::string rhs_type = _rhs->typecheck();
    
    if(lhs_type==rhs_type)
        return lhs_type;
    
    if((lhs_type=="double" && rhs_type=="int") || (lhs_type=="int" && rhs_type=="double"))
        return "double";
    else
        return "false";
}

std::string Variable_declaration::get_encapsulation(){
    
    return _encapsulation;
}

std::string Function_declaration::get_encapsulation(){
    
    return _encapsulation;
}

std::string Method_call::typecheck(){
    
    if(!_local_table.count(_varname))
        return "false";
    
    if(!_class_table.count(_local_table[_varname].get_type()[0]))
        return "false";
    
    for(auto decl : _class_table[_local_table[_varname].get_type()[0]].get_declarations())
        if(decl->get_name() == _name && decl->get_encapsulation() == "private")
            return "false";
    
    return _class_table[_local_table[_varname].get_type()[0]].get_type(_name);
}

std::string Attribute_call::typecheck(){
    
    if(!_local_table.count(_varname))
        return "false";
    
    if(!_class_table.count(_local_table[_varname].get_type()[0]))
        return "false";
    
    for(auto decl : _class_table[_local_table[_varname].get_type()[0]].get_declarations())
        if(decl->get_name() == _name && decl->get_encapsulation() == "private")
            return "false";
    
    return _class_table[_local_table[_varname].get_type()[0]].get_type(_name);
}

std::string Function_call::typecheck(){
    
    if(!_local_table.count(_name))
        return "false";
    else
        return _local_table[_name].typecheck();
} 















