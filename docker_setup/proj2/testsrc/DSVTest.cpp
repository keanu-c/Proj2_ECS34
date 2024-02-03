#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

#include <cstddef>

// From TA: Alex Young
TEST(DSVReader, HelloWorldTest){ //DSVReader TEST #1
    auto Source = std::make_shared<CStringDataSource>("Hello&World!");
    CDSVReader Reader(Source, '&');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    EXPECT_TRUE(Reader.End());
    ASSERT_EQ(output.size(),2);
    EXPECT_EQ(output[0],"Hello");
    EXPECT_EQ(output[1],"World!");
}
// From TA: Alex Young
TEST(DSVWriter, HelloWorldTest){ //DSVWriter TEST #1
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!");
}

TEST(DSVReader, EmptyStringTest){ //DSVReader TEST #2
    auto Source = std::make_shared<CStringDataSource>("");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_FALSE(Reader.ReadRow(output));
    EXPECT_TRUE(Reader.End());
}

TEST(DSVWriter, EmptyStringTest){ //DSVWriter TEST #2
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,',');
    std::vector<std::string> input = {""};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "");
}

TEST(DSVReader, DelimitersOnly){ //DSVReader TEST #3
    auto Source = std::make_shared<CStringDataSource>(" ; ; ; ");
    CDSVReader Reader(Source, ';');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    EXPECT_TRUE(Reader.End());
    ASSERT_EQ(output.size(), 4);
    EXPECT_EQ(output[0], "");
    EXPECT_EQ(output[1], "");
    EXPECT_EQ(output[2], "");
    EXPECT_EQ(output[3], "");
}

TEST(DSVWriter, DelimitersOnly){ //DSVWriter TEST #3
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,';');
    std::vector<std::string> input = {"", "", "", ""};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), " ; ; ; ");
}

TEST(DSVReader, CommasTest) { // DSVReader Test #4
    auto Source = std::make_shared<CStringDataSource>("Apple,of,my,Eye");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    EXPECT_TRUE(Reader.End());
    ASSERT_EQ(output.size(), 4);
    EXPECT_EQ(output[0], "Apple");
    EXPECT_EQ(output[1], "of");
    EXPECT_EQ(output[2], "my");
    EXPECT_EQ(output[3], "Eye");
}

TEST(DSVWriter, CommasTest) { // DSVWriter Test #4
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"Apple", "of", "my", "Eye"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "Apple,of,my,Eye");
}

TEST(DSVReader, MultipleRowsTest) { // DSVReader Test #5
    auto Source = std::make_shared<CStringDataSource>("Apple,of\nmy,Eye");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output1;

    EXPECT_TRUE(Reader.ReadRow(output1));
    ASSERT_EQ(output1.size(), 2);
    EXPECT_EQ(output1[0], "Apple");
    EXPECT_EQ(output1[1], "of");

    std::vector<std::string> output2;

    EXPECT_TRUE(Reader.ReadRow(output2));
    ASSERT_EQ(output2.size(), 2);
    EXPECT_EQ(output2[0], "my");
    EXPECT_EQ(output2[1], "Eye");
    
    EXPECT_TRUE(Reader.End());
}

TEST(DSVWriter, MultipleRowsTest){ // DSVWriter Test #5
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input1 = {"Apple", "of"};

    EXPECT_TRUE(Writer.WriteRow(input1));

    std::vector<std::string> input2 = {"my", "Eye"};
    EXPECT_TRUE(Writer.WriteRow(input2));
    EXPECT_EQ(Sink->String(), "Apple,of\nmy,Eye");
}

TEST(DSVReader, NoDelimiterTest) { // DSVReader Test #6
    auto Source = std::make_shared<CStringDataSource>("Apple");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(), 1);
    EXPECT_EQ(output[0], "Apple");
    EXPECT_TRUE(Reader.End());
}

TEST(DSVWriter, NoDelimiterTest) { // DSVWriter Test #6
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"Apple"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "Apple");
}

TEST(DSVReader, QuotesInMiddleTest) { // DSVReader Test #7
    auto Source = std::make_shared<CStringDataSource>("One,\"Two,Three\",Four");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(), 3);
    EXPECT_EQ(output[0], "One");
    EXPECT_EQ(output[1], "Two,Three");
    EXPECT_EQ(output[2], "Four");
    EXPECT_TRUE(Reader.End());
}

TEST(DSVWriter, QuotesInMiddleTest) { // DSVWriter Test #7
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"One", "Two,Three", "Four"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "One,\"Two,Three\",Four");
}

TEST(DSVReader, CrazyTest) { // DSVReader Test #8
    auto Source = std::make_shared<CStringDataSource>("\"\",\"\",\"\",\"\",\\\"\\\",\"\n\\n\\\\\n\",\",\"\"\",\"\"");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(), 8);
    EXPECT_EQ(output[0], "");
    EXPECT_EQ(output[1], "");
    EXPECT_EQ(output[2], "");
    EXPECT_EQ(output[3], "");
    EXPECT_EQ(output[4], "\"");
    EXPECT_EQ(output[5], "\n\\\n");
    EXPECT_EQ(output[6], ",");
    EXPECT_EQ(output[7], "");
    EXPECT_TRUE(Reader.End());
}

TEST(DSVWriter, CrazyTest) { // DSVWriter Test #8
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"", "", "", "", "\"", "\n\\\n", ",", ""};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"\"\",\"\",\"\",\"\",\\\"\\\",\"\n\\n\\\\\n\",\",\"\"\",\"\"");
}