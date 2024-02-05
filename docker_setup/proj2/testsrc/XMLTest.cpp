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
    auto Source = std::make_shared<CStringDataSource>("<note>\n<to attr=\"Hello World\">Tove</to>\n<from>Jani</from>\n<heading>Reminder</heading>\n<body>Don't forget me this weekend!</body>\n</note>");
    CXMLReader Reader(Source);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "note");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "\n");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

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

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "\n");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "from");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "Jani");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "from");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
 EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "\n");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "heading");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "Reminder");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "heading");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "\n");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "body");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "Don't forget me this weekend!");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "body");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "\n");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);
    
    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "note");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
}

TEST(XMLReaderTest, ComplexAttribute) {
    auto Source = std::make_shared<CStringDataSource>("<from gender=\"femaleasexual\">Jani</from>");
    CXMLReader Reader(Source);
    SXMLEntity Entity;

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "from");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::StartElement);
    EXPECT_EQ(Entity.AttributeValue("gender"), "femaleasexual");

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "Jani");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::CharData);

    EXPECT_TRUE(Reader.ReadEntity(Entity));
    EXPECT_EQ(Entity.DNameData, "from");
    EXPECT_EQ(Entity.DType, SXMLEntity::EType::EndElement);
    EXPECT_FALSE(Reader.ReadEntity(Entity));

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

    EXPECT_EQ(OutputStream->String(), "<hello attr=\"Hello &lt;&amp;&gt; World\"></hello>");
}

TEST(XMLWriterTest, MultipleElementXML) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "note", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {{"attr","Hello <&> World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "hello", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "note", {}}));

    EXPECT_EQ(OutputStream->String(), "<note><hello attr=\"Hello &lt;&amp;&gt; World\"></hello></note>");
}

TEST(XMLWriterTest, MultipleElementXML2) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "p", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "Some text ", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "b", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "bolded text", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "b", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, " some other text", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "p", {}}));

    EXPECT_EQ(OutputStream->String(), "<p>Some text <b>bolded text</b> some other text</p>");
}

TEST(XMLWriterTest, MultipleElementSpecialCharactersXML) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "note&", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello>", {{"attr","Hello <&> World"}}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "he\"llo", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::EndElement, "note", {}}));

    EXPECT_EQ(OutputStream->String(), "<note&amp;><hello&gt; attr=\"Hello &lt;&amp;&gt; World\"></he&quot;llo></note>");
}

TEST(XMLWriterTest, FlushTest) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "world", {}}));
    EXPECT_TRUE(Writer.Flush());

    EXPECT_EQ(OutputStream->String(), "<hello>world</hello>");
}

TEST(XMLWriterTest, FlushTest2) {
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "world", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "bye", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::StartElement, "yes", {}}));
    EXPECT_TRUE(Writer.WriteEntity({SXMLEntity::EType::CharData, "no", {}}));
    EXPECT_TRUE(Writer.Flush());

    EXPECT_EQ(OutputStream->String(), "<hello>world<bye><yes>no</yes></bye></hello>");
}