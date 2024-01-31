#include <gtest/gtest.h>
#include "StringUtils.h"

TEST(StringUtilsTest, SliceTest){
    std::string Base = "Hello";

    EXPECT_EQ(StringUtils::Slice(Base,0), "Hello");
    EXPECT_EQ(StringUtils::Slice(Base,1), "ello");
    EXPECT_EQ(StringUtils::Slice(Base,-1), "o");
    EXPECT_EQ(StringUtils::Slice(Base,-4), "ello");
    EXPECT_EQ(StringUtils::Slice(Base, -5), "Hello");
    EXPECT_EQ(StringUtils::Slice(Base, 6), "");
}

TEST(StringUtilsTest, Capitalize){
    std::string Base = "hello";
    
    EXPECT_EQ(StringUtils::Capitalize(Base), "Hello");
    EXPECT_EQ(StringUtils::Capitalize(std::string()), "");
    EXPECT_EQ(StringUtils::Capitalize(" hello"), " hello");
    EXPECT_EQ(StringUtils::Capitalize("HELLO"), "Hello");
    EXPECT_EQ(StringUtils::Capitalize("   \t\r\n*73"), "   \t\r\n*73");
}

TEST(StringUtilsTest, Upper){
    std::string Base = "hello";
    
    EXPECT_EQ(StringUtils::Upper(Base), "HELLO");
    EXPECT_EQ(StringUtils::Upper("one of !@#$best"), "ONE OF !@#$BEST");
    EXPECT_EQ(StringUtils::Upper("234!@"), "234!@");
    EXPECT_EQ(StringUtils::Upper("itwasthebest"), "ITWASTHEBEST");
    EXPECT_EQ(StringUtils::Upper(std::string()), "");
}

TEST(StringUtilsTest, Lower){
    std::string Base = "Hello";

    EXPECT_EQ(StringUtils::Lower(Base), "hello");
    EXPECT_EQ(StringUtils::Lower("ONE OF !@#$BEST"), "one of !@#$best");
    EXPECT_EQ(StringUtils::Lower("234!@"), "234!@");
    EXPECT_EQ(StringUtils::Lower("ITWASTHEBEST"), "itwasthebest");
    EXPECT_EQ(StringUtils::Lower(std::string()), "");
}

TEST(StringUtilsTest, LStrip){

    EXPECT_EQ(StringUtils::LStrip("    Hello"), "Hello");
    EXPECT_EQ(StringUtils::LStrip("Hello"), "Hello");
    EXPECT_EQ(StringUtils::LStrip("   123!!  "), "123!!  ");
    EXPECT_EQ(StringUtils::LStrip("  123!! !! "), "123!! !! ");
    EXPECT_EQ(StringUtils::LStrip(std::string()), "");
}

TEST(StringUtilsTest, RStrip){
    
    EXPECT_EQ(StringUtils::RStrip("Hello    "), "Hello");
    EXPECT_EQ(StringUtils::RStrip("Hello"), "Hello");
    EXPECT_EQ(StringUtils::RStrip("   123!!  "), "   123!!");
    EXPECT_EQ(StringUtils::RStrip("  123!! !! "), "  123!! !!");
    EXPECT_EQ(StringUtils::RStrip(std::string()), "");
}

TEST(StringUtilsTest, Strip){
    EXPECT_EQ(StringUtils::Strip("Hello    "), "Hello");
    EXPECT_EQ(StringUtils::Strip("Hello"), "Hello");
    EXPECT_EQ(StringUtils::Strip("   123!!  "), "123!!");
    EXPECT_EQ(StringUtils::Strip("  123!! !! "), "123!! !!");
    EXPECT_EQ(StringUtils::Strip(std::string()), "");
}

TEST(StringUtilsTest, Center){
    EXPECT_EQ(StringUtils::Center("Hello", 6, ' '), "Hello ");
    EXPECT_EQ(StringUtils::Center("Hello", 9, '-'), "--Hello--");
    EXPECT_EQ(StringUtils::Center("Hello", 10, '-'), "--Hello---");
    EXPECT_EQ(StringUtils::Center("12! H12", 12, ' '), "  12! H12   ");
    EXPECT_EQ(StringUtils::Center(" 12! H12 ", 14, '-'), "-- 12! H12 ---");
    EXPECT_EQ(StringUtils::Center(std::string(), 2, '-'), "--");
}

TEST(StringUtilsTest, LJust){
    EXPECT_EQ(StringUtils::LJust("Hello", 6, ' '), "Hello ");
    EXPECT_EQ(StringUtils::LJust("Hello", 9, '-'), "Hello----");
    EXPECT_EQ(StringUtils::LJust("12! H12", 12), "12! H12     ");
    EXPECT_EQ(StringUtils::LJust(" 12! H12 ", 14, '-'), " 12! H12 -----");
    EXPECT_EQ(StringUtils::LJust(std::string(), 2, '-'), "--");
}

TEST(StringUtilsTest, RJust){
    EXPECT_EQ(StringUtils::RJust("Hello", 6, ' '), " Hello");
    EXPECT_EQ(StringUtils::RJust("Hello", 9, '-'), "----Hello");
    EXPECT_EQ(StringUtils::RJust("12! H12", 12), "     12! H12");
    EXPECT_EQ(StringUtils::RJust(" 12! H12 ", 14, '-'), "----- 12! H12 ");
    EXPECT_EQ(StringUtils::RJust(std::string(), 2, '-'), "--");
}

TEST(StringUtilsTest, Replace){
    EXPECT_EQ(StringUtils::Replace("I really like apples", "apples", "bananas"), "I really like bananas");
    EXPECT_EQ(StringUtils::Replace("I apples like apples", "apples", "bananas"), "I bananas like bananas");
    EXPECT_EQ(StringUtils::Replace("  123#$ like apples  ", "123#$", "!*"), "  !* like apples  ");
    EXPECT_EQ(StringUtils::Replace("a&b*c/d", "&", "and"), "aandb*c/d");
    EXPECT_EQ(StringUtils::Replace("", "yes", "no"), "");

}

TEST(StringUtilsTest, Split){

    EXPECT_EQ(StringUtils::Split("I really like apples", " "), std::vector<std::string>({"I", "really", "like", "apples"}));
    EXPECT_EQ(StringUtils::Split("one two three"), std::vector<std::string>({"one", "two", "three"}));
    EXPECT_EQ(StringUtils::Split("-I really like apples", " "), std::vector<std::string>({"-I", "really", "like", "apples"}));
    EXPECT_EQ(StringUtils::Split("  -    123#$ like apples"), std::vector<std::string>({"-", "123#$", "like", "apples"}));
    EXPECT_EQ(StringUtils::Split(""), std::vector<std::string>());
    //EXPECT_EQ(StringUtils::Split("  hellooo and helloooo helloo  "), std::vector<std::string>({"hellooo", "and", "helloooo", "helloo "}));

}

TEST(StringUtilsTest, Join){
    EXPECT_EQ(StringUtils::Join("", std::vector<std::string>({"I", "really", "like", "apples"})), "Ireallylikeapples");
    EXPECT_EQ(StringUtils::Join("--", std::vector<std::string>({"I", "really", "like", "apples"})), "I--really--like--apples");
    EXPECT_EQ(StringUtils::Join(" ", std::vector<std::string>({"ab  ", "c", "  d"})), "ab   c   d");
    EXPECT_EQ(StringUtils::Join("", std::vector<std::string>({"ab ", "c", "d", "e  "})), "ab cde  ");
}

TEST(StringUtilsTest, ExpandTabs){
    EXPECT_EQ(StringUtils::ExpandTabs("H\te\tl\tl\to", 2), "H e l l o");
    EXPECT_EQ(StringUtils::ExpandTabs("H\te\tl\tl\to", 4), "H   e   l   l   o");
    EXPECT_EQ(StringUtils::ExpandTabs("\tH\tell\t\tl\to\t", 4), "    H   ell     l   o   ");
    EXPECT_EQ(StringUtils::ExpandTabs("\tH\tell  \t\tl\t  o\t", 2), "  H ell     l   o ");

}

TEST(StringUtilsTest, EditDistance){
    //AI generated
    EXPECT_EQ(StringUtils::EditDistance("xyz", "xyz"), 0);
    EXPECT_EQ(StringUtils::EditDistance("kitten", "sitting"), 3);
    EXPECT_EQ(StringUtils::EditDistance("hello", "HELLO", true), 0);
    EXPECT_EQ(StringUtils::EditDistance("hello", "HELLO", false), 5);
    EXPECT_EQ(StringUtils::EditDistance("", "xyz"), 3);
    EXPECT_EQ(StringUtils::EditDistance("", ""), 0);
}
