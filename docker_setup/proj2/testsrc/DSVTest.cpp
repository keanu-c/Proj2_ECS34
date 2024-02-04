#include <gtest/gtest.h>
#include "DSVReader.h"
#include "DSVWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

#include <cstddef>

// From TA: Alex Young
TEST(DSVReader, HelloWorldTest){
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
TEST(DSVWriter, HelloWorldTest){ 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'&');
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello&World!");
}

TEST(DSVWriter, HelloWorldTestWithDoubleQuote){ 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,'"');
    std::vector<std::string> input = {"Hello", "World!"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(),"Hello,World!");
}

TEST(DSVReader, EmptyStringTest){ 
    auto Source = std::make_shared<CStringDataSource>("");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    EXPECT_TRUE(Reader.End());
}

TEST(DSVWriter, EmptyStringTest){ 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,',');
    std::vector<std::string> input = {""};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "");
}

TEST(DSVReader, DelimitersOnly){ 
    auto Source = std::make_shared<CStringDataSource>(" ; ; ; ");
    CDSVReader Reader(Source, ';');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    EXPECT_TRUE(Reader.End());
    ASSERT_EQ(output.size(), 4);
    EXPECT_EQ(output[0], " ");
    EXPECT_EQ(output[1], " ");
    EXPECT_EQ(output[2], " ");
    EXPECT_EQ(output[3], " ");
}

TEST(DSVWriter, DelimitersOnly){ 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink,';');
    std::vector<std::string> input = {" ", " ", " ", " "};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), " ; ; ; ");
}

TEST(DSVReader, CommasTest) { 
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

TEST(DSVWriter, CommasTest) { 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"Apple", "of", "my", "Eye"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "Apple,of,my,Eye");
}

TEST(DSVReader, MultipleRowsTest) { 
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

TEST(DSVWriter, MultipleRowsTest){ 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');

    std::vector<std::string> input1 = {"Apple", "of"};
    EXPECT_TRUE(Writer.WriteRow(input1));
    EXPECT_EQ(Sink->String(), "Apple,of");

    std::vector<std::string> input2 = {"my", "Eye"};
    EXPECT_TRUE(Writer.WriteRow(input2));
    EXPECT_EQ(Sink->String(), "Apple,of\nmy,Eye");
}

TEST(DSVWriter, MultipleRowsTest2){ 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ';');

    std::vector<std::string> input1 = {"Apple", "of"};
    EXPECT_TRUE(Writer.WriteRow(input1));
    EXPECT_EQ(Sink->String(), "Apple;of");

    std::vector<std::string> input2 = {"my", "Eye"};
    EXPECT_TRUE(Writer.WriteRow(input2));
    EXPECT_EQ(Sink->String(), "Apple;of\nmy;Eye");

    std::vector<std::string> input3 = {"th\nis", "this"};
    EXPECT_TRUE(Writer.WriteRow(input3));
    EXPECT_EQ(Sink->String(), "Apple;of\nmy;Eye\nth\"\n\"is;this");

}

TEST(DSVReader, NoDelimiterTest) {
    auto Source = std::make_shared<CStringDataSource>("Apple");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(), 1);
    EXPECT_EQ(output[0], "Apple");
    EXPECT_TRUE(Reader.End());
}

TEST(DSVWriter, NoDelimiterTest) { 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"Apple"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "Apple");
}

TEST(DSVReader, QuotesInMiddleTest) { 
    auto Source = std::make_shared<CStringDataSource>("\"One\",\"Two Three\",\"Four\"");
    CDSVReader Reader(Source, ',');
    std::vector<std::string> output;

    EXPECT_TRUE(Reader.ReadRow(output));
    ASSERT_EQ(output.size(), 3);
    EXPECT_EQ(output[0], "\"One\"");
    EXPECT_EQ(output[1], "\"Two Three\"");
    EXPECT_EQ(output[2], "\"Four\"");
    EXPECT_TRUE(Reader.End());
}

TEST(DSVWriter, QuoteallTest) { 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',', true);
    std::vector<std::string> input = {"One", "TwoThree", "Four"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "\"One\",\"TwoThree\",\"Four\"");
}

TEST(DSVWriter, QuotesInMiddleTest1) { 
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"One", "Two\nThree", "Four"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "One,Two\"\n\"Three,Four");
}

TEST(DSVWriter, QuotesInMiddleTest2) {
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"One", "Two,Three", "Four"};

    EXPECT_TRUE(Writer.WriteRow(input));
    EXPECT_EQ(Sink->String(), "One,Two\",\"Three,Four");
}