CC=gcc
CXX=g++

INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
TEST_SRC_DIR = ./testsrc

CXXFLAGS = -std=c++17 -I $(INC_DIR)
#linking files
LDFLAGS = -L /usr/local/lib -lgtest -lgtest_main -lpthread -lexpat

all: directories runtests

runtests: $(BIN_DIR)/teststrutils $(BIN_DIR)/teststrdatasource $(BIN_DIR)/teststrdatasink
	$(BIN_DIR)/teststrutils
	$(BIN_DIR)/teststrdatasource
	$(BIN_DIR)/teststrdatasink

# teststrutils
$(BIN_DIR)/teststrutils: $(OBJ_DIR)/StringUtils.o $(OBJ_DIR)/StringUtilsTest.o
	$(CXX) -o $(BIN_DIR)/teststrutils $(CXXFLAGS) $(OBJ_DIR)/StringUtils.o $(OBJ_DIR)/StringUtilsTest.o $(LDFLAGS)


$(OBJ_DIR)/StringUtils.o: $(SRC_DIR)/StringUtils.cpp $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/StringUtils.o -c $(CXXFLAGS) $(SRC_DIR)/StringUtils.cpp

$(OBJ_DIR)/StringUtilsTest.o: $(TEST_SRC_DIR)/StringUtilsTest.cpp $(INC_DIR)/StringUtils.h
	$(CXX) -o $(OBJ_DIR)/StringUtilsTest.o -c $(CXXFLAGS) $(TEST_SRC_DIR)/StringUtilsTest.cpp

# teststrdatasource
$(BIN_DIR)/teststrdatasource: $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringDataSourceTest.o
	$(CXX) -o $(BIN_DIR)/teststrdatasource $(CXXFLAGS) $(OBJ_DIR)/StringDataSource.o $(OBJ_DIR)/StringDataSourceTest.o $(LDFLAGS)


$(OBJ_DIR)/StringDataSource.o: $(SRC_DIR)/StringDataSource.cpp $(INC_DIR)/StringDataSource.h
	$(CXX) -o $(OBJ_DIR)/StringDataSource.o -c $(CXXFLAGS) $(SRC_DIR)/StringDataSource.cpp

$(OBJ_DIR)/StringDataSourceTest.o: $(TEST_SRC_DIR)/StringDataSourceTest.cpp $(INC_DIR)/StringDataSource.h
	$(CXX) -o $(OBJ_DIR)/StringDataSourceTest.o -c $(CXXFLAGS) $(TEST_SRC_DIR)/StringDataSourceTest.cpp

# teststrdatasink
$(BIN_DIR)/teststrdatasink: $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/StringDataSinkTest.o
	$(CXX) -o $(BIN_DIR)/teststrdatasink $(CXXFLAGS) $(OBJ_DIR)/StringDataSink.o $(OBJ_DIR)/StringDataSinkTest.o $(LDFLAGS)


$(OBJ_DIR)/StringDataSink.o: $(SRC_DIR)/StringDataSink.cpp $(INC_DIR)/StringDataSink.h
	$(CXX) -o $(OBJ_DIR)/StringDataSink.o -c $(CXXFLAGS) $(SRC_DIR)/StringDataSink.cpp

$(OBJ_DIR)/StringDataSinkTest.o: $(TEST_SRC_DIR)/StringDataSinkTest.cpp $(INC_DIR)/StringDataSink.h
	$(CXX) -o $(OBJ_DIR)/StringDataSinkTest.o -c $(CXXFLAGS) $(TEST_SRC_DIR)/StringDataSinkTest.cpp

# testdsv


# testxml


clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)

# -p says it's ok if the path already exists
directories:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)