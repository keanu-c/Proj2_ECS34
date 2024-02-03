#include <gtest/gtest.h>
#include "XMLReader.h"
#include "XMLWriter.h"
#include "StringDataSink.h"
#include "StringDataSource.h"

// Make sure to check for complete elements, elements with attributes, multiple line xml's 
// XML READER ------------------------------------------------------------------------------------------------------------------------------------
TEST(XMLReaderTest, SimpleXML) {
    auto Source = std::make_shared<CStringDataSource>("<heading>Reminder</heading>");
    CXMLReader Reader(Source);
    SXMLEntity Entity;
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "heading");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "Reminder");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "heading");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);

    EXPECT_FALSE(Reader.ReadEntity(Entity));
}

TEST(XMLReaderTest, SimpleXMLWithAttribute) {
    auto Source = std::make_shared<CStringDataSource>("<heading attr=\"Hello World\">Reminder</heading>");
    CXMLReader Reader(Source);
    SXMLEntity Entity;
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "heading");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.AttributeValue("attr"), "Hello World");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "Reminder");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "heading");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_FALSE(Reader.ReadEntity(Entity));
}

TEST(XMLReaderTest, EmptyXML) {
    auto Source = std::make_shared<CStringDataSource>("");
    CXMLReader Reader(Source);
    EXPECT_TRUE(Reader.End());
}

TEST(XMLReaderTest, MultipleLineXML) {
    auto Source = std::make_shared<CStringDataSource>("<note>\n  <to attr=\"Hello World\"Tove</to>\n  <from>Jani</from>\n  <heading>Reminder</heading>\n  <body>Don't forget me this weekend!</body>\n  </note>");
    CXMLReader Reader(Source);
    SXMLEntity Entity;
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "note");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "to");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.AttributeValue("attr"), "Hello World");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "Tove");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "to");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity)); // <from>
    EXPECT_TRUE(Reader.ReadEntity(Entity)); // Jani
    EXPECT_TRUE(Reader.ReadEntity(Entity)); // </from>
    EXPECT_TRUE(Reader.ReadEntity(Entity)); // <heading>
    EXPECT_TRUE(Reader.ReadEntity(Entity)); // Reminder
    EXPECT_TRUE(Reader.ReadEntity(Entity)); // </heading>
    EXPECT_TRUE(Reader.ReadEntity(Entity)); // <body>
    EXPECT_TRUE(Reader.ReadEntity(Entity)); // Don't forget me this weekend!
    EXPECT_TRUE(Reader.ReadEntity(Entity)); // </body>
    
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "note");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLReaderTest, ComplexAttribute) {
    auto Source = std::make_shared<CStringDataSource>("<from gender=\"female & asexual\">Jani</from>");
    CXMLReader Reader(Source);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "from");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.AttributeValue("gender"), "female & asexual");
}

// XML WRITER ----------------------------------------------------------------------------------------------------------------------------------------------------------------

TEST(XMLWriterTest, SimpleTest) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "hello", {}}));

    EXPECT_EQ(OutputStream->String(), "<hello></hello>");
    
}

TEST(XMLWriterTest, SimpleXMLWithAttribute) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {{"attr","Hello <&> World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "hello", {}}));

    EXPECT_EQ(OutputStream->String(), "<hello attr=\"Hello <&> World\"></hello>");
}

TEST(XMLWriterTest, MultipleElementXML) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "note", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {{"attr","Hello <&> World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "hello", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "note", {}}));

    EXPECT_EQ(OutputStream->String(), "<note><hello attr=\"Hello <&> World\"></hello></note>");
}

TEST(XMLWriterTest, NewlineXML) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);
    // HOW DO I ADD NEWLINE
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "note", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {{"attr","Hello <&> World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "hello", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "note", {}}));

    EXPECT_EQ(OutputStream->String(), "<note>\n  <hello attr=\"Hello <&> World\"></hello>\n</note>");
}

