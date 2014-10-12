#include "libfb2k/FuncMap.h"
#include "libfb2k/error.h"
#include <sstream>
using namespace fb2k;

FuncMap::FuncMap()
{
    enableControlFuncs();
    enableBoolFuncs();
    enableMathsFuncs();
}

FuncMap::FuncMap(bool enableDefaults)
{
    if (enableDefaults) {
        enableControlFuncs();
        enableBoolFuncs();
        enableMathsFuncs();
    }
}

bool FuncMap::check(std::string name, std::vector<Block> args)
{
    if (find(name) != end()) {
        return (*this) [name].check(args.size());
    }

    throw fb2k::InvalidFunctionName("Unknown Function name");
}

void FuncMap::insert(Func function)
{
    if (function.check != nullptr && function.check != nullptr) {
        if (this->find(function.name) == this->end()) {
            map::insert<FuncPair> (FuncPair(function.name, function));
        } else {
            std::stringstream ss;
            ss << "Duplicate of the function " << function.name << " defined";
            throw fb2k::FB2KError(ss.str());
        }
    } else {
        std::stringstream ss;
        ss << "A function with no check or eval methods attempted to be added with the name " << function.name;
        throw fb2k::FB2KError(ss.str());
    }
}

void FuncMap::insertOverride(Func function)
{
    map::insert<FuncPair> (FuncPair(function.name, function));
}

FuncMap::~FuncMap()
{

}

void FuncMap::enableControlFuncs()
{
    //Implicit if
    this->insertOverride(Func("[",
    [](TagLib::PropertyMap data , std::vector<Block> args) {
        auto result = args[0].eval(data);

        if (result.success) {
            // TRUE
            return result;
        } else {
            //FALSE
            return BlockResult();
        }
    },
    [](unsigned int argscount) {
        if (argscount == 1) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected 1 argument for []");
        }
    }));

    // Basic Conditionals
    this->insertOverride(Func("if",
    [](TagLib::PropertyMap data , std::vector<Block> args) {

        if (args[0].eval(data).success) {
            //TRUE
            return args[1].eval(data);
        } else {
            //FALSE
            return (args.size() == 3 ? args[2].eval(data) : BlockResult());
        }

    },
    [](unsigned int argscount) {
        if (argscount == 2 || argscount == 3) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected 2 or greater arguments for if");
        }
    }));

    this->insertOverride(Func("if2",
    [](TagLib::PropertyMap data , std::vector<Block> args) {

        auto result = args[0].eval(data);

        if (result.success) {
            //TRUE
            return result;
        } else {
            //FALSE
            return args[1].eval(data);
        }

    },
    [](unsigned int argscount) {
        if (argscount == 2) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected 2 arguments for if2");
        }
    }));

    // if with guaranteed 3 arguments
    this->insertOverride(Func("if3",
    [](TagLib::PropertyMap data , std::vector<Block> args) {

        // Check a1..aN if true, return
        for (unsigned int i = 0; i < args.size() - 1; i++) {
            BlockResult result = args[i].eval(data);

            if (result.success) {
                return result;
            }
        }

        // return `else` if a1..aN is all false
        return args[args.size() - 1].eval(data);
    },
    [](unsigned int argscount) {
        if (argscount >= 3) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected 2 or greater arguments for if3");
        }
    }));
}


void FuncMap::enableBoolFuncs()
{
// Logical Operators
    // NOTE :  Logical Operators DO NOT return result strings, just a boolean
    // TODO: add implies, equals and equivalent
    this->insertOverride(Func("not",
    [](TagLib::PropertyMap data , std::vector<Block> args) {

        BlockResult rs;
        rs.success = (!args[0].eval(data).success);
        return rs;

    },
    [](unsigned int argscount) {
        if (argscount == 1) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected only 1 argument for not");
        }
    }));

    this->insertOverride(Func("or",
    [](TagLib::PropertyMap data , std::vector<Block> args) {

        BlockResult rs;
        rs.success = false;

        for (auto & arg : args) {
            if (arg.eval(data).success) {
                rs.success = true;
                return rs;
            }
        }

        return rs;

    },
    [](unsigned int argscount) {
        if (argscount >= 2) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected 2 or greater arguments for or");
        }
    }));

    this->insertOverride(Func("xor",
    [](TagLib::PropertyMap data , std::vector<Block> args) {

        BlockResult rs;
        rs.success = false;

        for (auto & arg : args) {
            if (arg.eval(data).success) {
                rs.success = !rs.success;
            }
        }

        return rs;
    },
    [](unsigned int argscount) {
        if (argscount >= 2) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected 2 or greater arguments for xor");
        }
    }));

    this->insertOverride(Func("and",
    [](TagLib::PropertyMap data , std::vector<Block> args) {

        BlockResult rs;
        rs.success = true;

        for (auto & arg : args) {
            if (!arg.eval(data).success) {
                rs.success = false;
                return rs;
            }
        }

        return rs;
    },
    [](unsigned int argscount) {
        if (argscount >= 2) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected 2 or greater arguments for and");
        }
    }));
}

void FuncMap::enableMathsFuncs()
{
    // Returns a string with that represents the value that was calculated
    this->insertOverride(Func("add",
    [](TagLib::PropertyMap data , std::vector<Block> args) {

        BlockResult rs;

        for (auto & arg : args) {
            rs.value += arg.eval(data).value;
        }

        rs.result = std::to_string(rs.value);
        return rs;

    },
    [](unsigned int argscount) {
        if (argscount >= 2) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected only 2 or greater arguments for add");
        }
    }));

    this->insertOverride(Func("sub",
    [](TagLib::PropertyMap data , std::vector<Block> args) {
        // ((a-b)-c)...
        BlockResult rs;
        rs.value = args[0].eval(data).value;

        for (unsigned int i = 1; i < args.size(); i++) {
            rs.value -= args[i].eval(data).value;
        }

        rs.result = std::to_string(rs.value);
        return rs;

    },
    [](unsigned int argscount) {
        if (argscount >= 2) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected only 2 or greater arguments for sub");
        }
    }));

    this->insertOverride(Func("div",
    [](TagLib::PropertyMap data , std::vector<Block> args) {
        //Is ((a/b)/c)...
        BlockResult rs;
        int a = args[0].eval(data).value;

        for (unsigned int i = 1; i < args.size(); i++) {
            int b = args[i].eval(data).value;

            if (b != 0) {
                a /= b;
            }
        }

        rs.value = a;
        rs.result = std::to_string(rs.value);
        return rs;

    },
    [](unsigned int argscount) {
        if (argscount >= 2) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected only 2 or greater arguments for div");
        }
    }));

    this->insertOverride(Func("mul",
    [](TagLib::PropertyMap data , std::vector<Block> args) {
        //Is ((a/b)/c)...
        BlockResult rs;
        int a = args[0].eval(data).value;

        for (unsigned int i = 1; i < args.size(); i++) {
            int b = args[i].eval(data).value;
            a *= b;
        }

        rs.value = a;
        rs.result = std::to_string(rs.value);
        return rs;

    },
    [](unsigned int argscount) {
        if (argscount >= 2) {
            return true;
        } else {
            throw InvalidNumberOfArugments("Expected only 2 or greater arguments for mul");
        }
    }));
}
