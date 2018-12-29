cmake_minimum_required(VERSION 3.13)
project(prog1Project)
set(CMAKE_CXX_STANDARD 14)

set (SOURCE_FILES src/main.cpp src/Command.h src/Expression.h src/Expressions.h src/Interpreter.h src/Interpreter.cpp src/Utils.h src/Utils.cpp src/Enviroment.cpp src/Enviroment.h)
set (COMMANDS_SOURCE_FILES src/Commands/ConditionParser.h src/Commands/ConditionParser.cpp src/Commands/DefineVarCommand.h src/Commands/DefineVarCommand.cpp src/Commands/EqualsCommand.cpp src/Commands/EqualsCommand.h src/Commands/IfCommand.h src/Commands/IfCommand.cpp src/Commands/OpenDataServerCommand.cpp src/Commands/OpenDataServerCommand.h src/Commands/PrintCommand.cpp src/Commands/PrintCommand.h src/Commands/SemicolonCommand.h src/Commands/WhileCommand.h src/Commands/WhileCommand.cpp src/Commands/ConnectCommand.h src/Commands/ConnectCommand.cpp src/Commands/CommandCreator.h src/Commands/SleepCommand.cpp src/Commands/SleepCommand.h src/Commands/EnterCCommand.h)
set (EXPRESSIONS_SOURCE_FILES src/Expressions/ExpressionFactory.cpp src/Expressions/ExpressionFactory.h src/Expressions/Number.h src/Expressions/UnaryExpression.h src/Expressions/Var.h src/Expressions/BooleanExpressions/Bigger.h src/Expressions/BooleanExpressions/Equals.h src/Expressions/BooleanExpressions/NotEquals.h src/Expressions/BooleanExpressions/Smaller.h src/Expressions/Expressions_operators/Div.h src/Expressions/Expressions_operators/Mul.h src/Expressions/Expressions_operators/Minus.h src/Expressions/Expressions_operators/Plus.h src/Expressions/Expressions_operators/Pow.h src/Expressions/Expressions_operators/Neg.h src/Sockets/FlightDataGetterSetter.cpp src/Sockets/FlightDataGetterSetter.h src/Symbol.h src/Commands/Creators.h)
set (DATABASES_SOUCE_FILES src/Databases/ConstsDB.cpp src/Databases/ConstsDB.h src/Databases/SymbolsDB.cpp src/Databases/SymbolsDB.h src/Exceptions.h)
set (CMAKE_CXX_FLAGS -pthread)

add_executable(prog1Project ${DATABASES_SOURCE_FILES} ${COMMANDS_SOURCE_FILES} ${EXPRESSIONS_SOURCE_FILES} ${SOURCE_FILES})