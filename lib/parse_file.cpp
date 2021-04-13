/*
 * Author: Partha Sarthy
 * Date: 04.07.2021 - 04.08.2021
 *
 * Features:
 * =========
 * 1. Parses all the typedefs, function names, macros, comments and globals.
 * 2. Modifies the formal arguments (numeric / string data types) before passing to the base library function.
 * 3. Logs the following in each of the interposed library function:
 *   i.  Time.
 *   ii. Function name and parameters
 *   iii. Return values from the base library functions.
 * 4. Each function finds the name of the corresponding base library function with the help of dlsym().
 *
 * Assumptions:
 * ============
 * 1. The data types recognized and implemented here are those in the vector data_types.
 * 2. Not more than one space between tokens.
 *
 * Limitations:
 * ============
 * 1. While parsing the signatures of functions, qualifiers like const have been omitted.
 * 2. User defined data types like structures have not been implemented.
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iterator>
#include <map>

using namespace std;

#define RET_STRING  "return ret;"
#define TAB_STRING  "\t"
// Following are the extra header files imported in the resultant C code.
#define TIME_HDR_STRING     "#include <time.h>"
#define DL_HDR_STRING       "#include <dlfcn.h>"
#define FILE_HDR_STRING     "#include <fstream.h>"
// Preprocessor directives
const char* pre_process_dir[] = {"#include", "#define", "#ifdef", "#ifndef", "#endif"};
// This vector holds the data types and the typedefs
vector<const char*> data_types {"char*", "bool*", "int*", "float*", "double*", "void*", "uint32_t", "size_t", "char", "bool", "int", "float", "double", "void"};

string typedef_name;
/*
 * To generate the extra header files needed.
 */
void header_content(ofstream &fout) {
    fout<<TIME_HDR_STRING<<endl;
    fout<<DL_HDR_STRING<<endl;
    fout<<FILE_HDR_STRING<<endl;
    return;
}
/*
 * To generate the statements of the logging utility.
 */
void logging_content(string fn_name, string fn_sign, string &fn_content) {
    string log_content;
    log_content += "\tFILE* fout;\n";
    log_content += "\tfout = fopen(\"lattice_lib.log\", \"w+\");\n";
    log_content += "\tstruct tm* current_time; time_t s;\n";
    log_content += "\ts = time(NULL);\n";
    log_content += "\tcurrent_time = localtime(&s);\n";
    log_content += "\tfprintf(fout, \"%d:%d:%d::%s%s\",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);\n";
    log_content += "\tfprintf(fout, \"%d:%d:%d::%s::return value = %d\",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);\n";
    log_content += "\tfclose(fout);\n";
    fn_content += log_content;
    return;
}
/*
 * To generate the statements of the dynamic linking functionality.
 */
void dyn_linking_content(string fn_name, string fn_sign, string &fn_content) {
    string dl_content;
    dl_content += "\tint ret;\n";
    dl_content += "\tvoid* handle;\n";
    dl_content += "\tvoid (*base_fn_name)" + fn_sign +");\n";
    dl_content += "\thandle = dlopen(\"./liblatticeinterposed.so\", RTLD_NOW);\n";
    dl_content += "\t*(void*)(base_fn_name) = dlsym(handle, " + fn_name+");\n";
    dl_content += "\t if (!base_fn_name) {\n";
    dl_content += "\t\tprintf(\"Error\");\n";
    dl_content += "\t\tdlclose(handle);\n";
    dl_content += "\t\treturn 0;\n";
    dl_content += "\t}\n";
    dl_content += "\tret = base_fn_name" + fn_sign + ");\n";
    dl_content += "\tdlclose(handle);\n";
    fn_content += dl_content;
    return;
}
/*
 * To modify numeric and character data types.
 */
void modify_inplace(string param_type, string param, string &fn_content) {
    if (!strcmp(param_type.c_str(), "int") || !strcmp(param_type.c_str(), "float") || !strcmp(param_type.c_str(), "double")|| !strcmp(param_type.c_str(), "size_t")){
        fn_content += "\t//Manipulating " + param_type + " parameters.\n";
        fn_content += ("\t" + param + " *= 2;\n");
        if (!strcmp(param_type.c_str(), "int") || !strcmp(param_type.c_str(), "size_t"))
            fn_content += "\tprintf(\"Modified param to %d.\\n\", param);\n";
        if (!strcmp(param_type.c_str(), "float") || !strcmp(param_type.c_str(), "double"))
            fn_content += "\tprintf(\"Modified param to %f.\n\", param);\n";
        return;
    }
    if (!strcmp(param_type.c_str(), "char*") || !strcmp(param_type.c_str(), "string")) {
        fn_content += "\t//Manipulating " + param_type + " parameters.\n";
        fn_content += "\tchar *" + param +"_temp = strrev(" + param +");\n";
        fn_content += "\tprintf(\"Reversed string %s to %s.\\n\", " + param +", str2);\n";
        fn_content += "\tstrcpy(" + param + ", str2);\n";
        return;
    }
}
/*
 * To parse the formal parameters for the functions.
 */
bool parse_fn_signature(string line, ofstream &fout, ifstream &finp, string &fn_content) {
    char *t;
    char delim[] = "(,)";
    char line_str[line.length() + 1];
    int var_name_start;
    string var_name;
    vector<string> params;
    vector<const char*>::iterator ptr;

    strcpy(line_str, line.c_str());
    t = strtok(line_str, delim);
    while (t) {
        params.push_back(t);
        t = strtok(NULL, ",");
    }
    for (int i = 0; i < params.size(); i++) {
        for (ptr = data_types.begin(); ptr != data_types.end(); ptr++) {
            if (strstr(params[i].c_str(), *ptr)) {
                var_name_start = params[i].find(*ptr) + strlen(*ptr);
                var_name = params[i].substr(var_name_start + 1, strlen(params[i].c_str()) - params[i].find(*ptr));
                modify_inplace(*ptr, var_name, fn_content);
                break;
            }
        }
    }
}
/*
 * To parse the typedefs in the file and store in the global data_types vector.
 */
bool parse_typedefs(string line, ofstream &fout, ifstream &finp) {
    int s = data_types.size();
    int typedef_name_start;
    vector<const char*>::iterator ptr;
    if (strstr(line.c_str(), "typedef")) {
        for (ptr = data_types.begin(); ptr < data_types.end(); ptr++) {
            if (strstr(line.c_str(), *ptr)) {
                typedef_name_start = line.find(*ptr) + strlen(*ptr);
                typedef_name = line.substr(typedef_name_start + 1, strlen(line.c_str()) - strlen("typedef") - strlen(*ptr) - 3);
                data_types.insert(data_types.begin(), typedef_name.c_str());
                break;
            }
        }
        fout<<line<<endl;
        return true;
    }
    return false;
}
/*
 * To parse the function declarations and generate the function definitions.
 */
bool parse_functions(string line, ofstream &fout, ifstream &finp) {
    int pos_semicolon, pos_fn_name_start, pos_fn_name_end, s = data_types.size();;
    string fn_name;
    string fn_name_wo_sign;
    string fn_sign;
    string fn_content;
    vector<const char*>::iterator ptr;

    if (strchr(line.c_str(), ';')) {
        pos_semicolon = line.find(';');
        line.replace(pos_semicolon, 1, " {");
        pos_fn_name_end = line.find('(');
        fn_name_wo_sign = line.substr(0, pos_fn_name_end);
        fn_sign = line.substr(pos_fn_name_end, strlen(line.c_str()) - pos_fn_name_end - 3);
        parse_fn_signature(fn_sign, fout, finp, fn_content);

        for (ptr = data_types.begin(); ptr < data_types.end(); ptr++) {
            if (strstr(fn_name_wo_sign.c_str(), *ptr)) {
                pos_fn_name_start = line.find(*ptr) + strlen(*ptr);
                break;
            }
        }
        fn_name = line.substr(pos_fn_name_start + 1, pos_fn_name_end - pos_fn_name_start - 1);
        dyn_linking_content(fn_name, fn_sign, fn_content);
        logging_content(fn_name, fn_sign, fn_content);
        fout<<line<<endl;
        fout<<fn_content<<endl;
        fout<<TAB_STRING<<RET_STRING<<endl;
        fout<<"}"<<endl;
        return true;
    } else {
        fout<<line<<endl;
        return true;
    }
    return false;
}
/*
 * To parse the multi-line comments.
 */
bool parse_multi_comments(string line, ofstream &fout, ifstream &finp) {
    if (strstr(line.c_str(), "/*")) {
        fout<<line<<endl;
        while (1) {
            getline(finp, line);
            if (strstr(line.c_str(), "*/")) {
                fout<<line<<endl;
                return true;
            } else {
                fout<<line<<endl;
            }
        }
    }
    return false;
}
/*
 * To parse the single-line comments.
 */
bool parse_single_comments(string line, ofstream &fout, ifstream &finp) {
    if (strstr(line.c_str(), "//")) {
        fout<<line<<endl;
        return true;
    }
    if (strstr(line.c_str(), "/*") && strstr(line.c_str(), "*/")) {
        fout<<line<<endl;
        return true;
    }
    return false;
}
/*
 * To parse the global variables.
 */
bool parse_globals(string line, ofstream &fout, ifstream &finp) {
    if (strchr(line.c_str(), ';') && !strchr(line.c_str(), '(')) {
        fout<<line<<endl;
        return true;
    }
    return false;
}
/*
 * To parse the preprocessor directives.
 */
bool parse_preprocess(string line, ofstream &fout, ifstream &finp) {
    int i, s = int(sizeof(pre_process_dir) / sizeof(pre_process_dir[0]));
    for (i = 0; i < s; i++)
    {
        if (strstr(line.c_str(), pre_process_dir[i])) {
            fout<<line<<endl;
            return true;
        }
    }
    return false;
}
/*
 * Array of function pointers.
 */
bool (*parse_call[])(string, ofstream&, ifstream&) = {parse_preprocess,
                                                      parse_typedefs,
                                                      parse_single_comments,
                                                      parse_multi_comments,
                                                      parse_globals,
                                                      parse_functions};
/*
 * Driver code.
 */
int main() {
    ifstream finp;
    ofstream fout;
    string line;
    int i, s = (int)(sizeof(parse_call) / sizeof(parse_call[0]));

    finp.open("lattice.h");
    fout.open("lattice_int.c");
    header_content(fout);
    while (finp) {
        getline(finp, line);
        for (i = 0; i < s; i++) {
            if((*parse_call[i])(line, fout, finp)){
                break;
            }
        }
    }
    fout.close();
    finp.close();
    finp.open("lattice_int.c");
    while (finp) {
        getline(finp, line);
        cout<<line<<endl;
    }
    finp.close();
    return 0;
}


