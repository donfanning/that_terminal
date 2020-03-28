#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <string_view>
#include <cstdio>

#include <gd.h>

namespace authentic
{
#include "fonts-authentic.inc"
#include "fonts-list.inc"
}
namespace pseudo
{
#include "fonts.inc"
#include "fonts-list.inc"
}
#include "../ctype.hh"

static const std::tuple<unsigned,unsigned,std::string_view> blocks[]
{
{ 0x0000, 0x007F, "Basic Latin" },
{ 0x0080, 0x00FF, "Latin-1 Supplement" },
{ 0x0100, 0x017F, "Latin Extended-A" },
{ 0x0180, 0x024F, "Latin Extended-B" },
{ 0x0250, 0x02AF, "IPA Extensions" },
{ 0x02B0, 0x02FF, "Spacing Modifier Letters" },
{ 0x0300, 0x036F, "Combining Diacritical Marks" },
{ 0x0370, 0x03FF, "Greek and Coptic" },
{ 0x0400, 0x04FF, "Cyrillic" },
{ 0x0500, 0x052F, "Cyrillic Supplement" },
{ 0x0530, 0x058F, "Armenian" },
{ 0x0590, 0x05FF, "Hebrew" },
{ 0x0600, 0x06FF, "Arabic" },
{ 0x0700, 0x074F, "Syriac" },
{ 0x0750, 0x077F, "Arabic Supplement" },
{ 0x0780, 0x07BF, "Thaana" },
{ 0x07C0, 0x07FF, "NKo" },
{ 0x0800, 0x083F, "Samaritan" },
{ 0x0840, 0x085F, "Mandaic" },
{ 0x0860, 0x086F, "Syriac Supplement" },
{ 0x08A0, 0x08FF, "Arabic Extended-A" },
{ 0x0900, 0x097F, "Devanagari" },
{ 0x0980, 0x09FF, "Bengali" },
{ 0x0A00, 0x0A7F, "Gurmukhi" },
{ 0x0A80, 0x0AFF, "Gujarati" },
{ 0x0B00, 0x0B7F, "Oriya" },
{ 0x0B80, 0x0BFF, "Tamil" },
{ 0x0C00, 0x0C7F, "Telugu" },
{ 0x0C80, 0x0CFF, "Kannada" },
{ 0x0D00, 0x0D7F, "Malayalam" },
{ 0x0D80, 0x0DFF, "Sinhala" },
{ 0x0E00, 0x0E7F, "Thai" },
{ 0x0E80, 0x0EFF, "Lao" },
{ 0x0F00, 0x0FFF, "Tibetan" },
{ 0x1000, 0x109F, "Myanmar" },
{ 0x10A0, 0x10FF, "Georgian" },
{ 0x1100, 0x11FF, "Hangul Jamo" },
{ 0x1200, 0x137F, "Ethiopic" },
{ 0x1380, 0x139F, "Ethiopic Supplement" },
{ 0x13A0, 0x13FF, "Cherokee" },
{ 0x1400, 0x167F, "Unified Canadian Aboriginal Syllabics" },
{ 0x1680, 0x169F, "Ogham" },
{ 0x16A0, 0x16FF, "Runic" },
{ 0x1700, 0x171F, "Tagalog" },
{ 0x1720, 0x173F, "Hanunoo" },
{ 0x1740, 0x175F, "Buhid" },
{ 0x1760, 0x177F, "Tagbanwa" },
{ 0x1780, 0x17FF, "Khmer" },
{ 0x1800, 0x18AF, "Mongolian" },
{ 0x18B0, 0x18FF, "Unified Canadian Aboriginal Syllabics Extended" },
{ 0x1900, 0x194F, "Limbu" },
{ 0x1950, 0x197F, "Tai Le" },
{ 0x1980, 0x19DF, "New Tai Lue" },
{ 0x19E0, 0x19FF, "Khmer Symbols" },
{ 0x1A00, 0x1A1F, "Buginese" },
{ 0x1A20, 0x1AAF, "Tai Tham" },
{ 0x1AB0, 0x1AFF, "Combining Diacritical Marks Extended" },
{ 0x1B00, 0x1B7F, "Balinese" },
{ 0x1B80, 0x1BBF, "Sundanese" },
{ 0x1BC0, 0x1BFF, "Batak" },
{ 0x1C00, 0x1C4F, "Lepcha" },
{ 0x1C50, 0x1C7F, "Ol Chiki" },
{ 0x1C80, 0x1C8F, "Cyrillic Extended-C" },
{ 0x1C90, 0x1CBF, "Georgian Extended" },
{ 0x1CC0, 0x1CCF, "Sundanese Supplement" },
{ 0x1CD0, 0x1CFF, "Vedic Extensions" },
{ 0x1D00, 0x1D7F, "Phonetic Extensions" },
{ 0x1D80, 0x1DBF, "Phonetic Extensions Supplement" },
{ 0x1DC0, 0x1DFF, "Combining Diacritical Marks Supplement" },
{ 0x1E00, 0x1EFF, "Latin Extended Additional" },
{ 0x1F00, 0x1FFF, "Greek Extended" },
{ 0x2000, 0x206F, "General Punctuation" },
{ 0x2070, 0x209F, "Superscripts and Subscripts" },
{ 0x20A0, 0x20CF, "Currency Symbols" },
{ 0x20D0, 0x20FF, "Combining Diacritical Marks for Symbols" },
{ 0x2100, 0x214F, "Letterlike Symbols" },
{ 0x2150, 0x218F, "Number Forms" },
{ 0x2190, 0x21FF, "Arrows" },
{ 0x2200, 0x22FF, "Mathematical Operators" },
{ 0x2300, 0x23FF, "Miscellaneous Technical" },
{ 0x2400, 0x243F, "Control Pictures" },
{ 0x2440, 0x245F, "Optical Character Recognition" },
{ 0x2460, 0x24FF, "Enclosed Alphanumerics" },
{ 0x2500, 0x257F, "Box Drawing" },
{ 0x2580, 0x259F, "Block Elements" },
{ 0x25A0, 0x25FF, "Geometric Shapes" },
{ 0x2600, 0x26FF, "Miscellaneous Symbols" },
{ 0x2700, 0x27BF, "Dingbats" },
{ 0x27C0, 0x27EF, "Miscellaneous Mathematical Symbols-A" },
{ 0x27F0, 0x27FF, "Supplemental Arrows-A" },
{ 0x2800, 0x28FF, "Braille Patterns" },
{ 0x2900, 0x297F, "Supplemental Arrows-B" },
{ 0x2980, 0x29FF, "Miscellaneous Mathematical Symbols-B" },
{ 0x2A00, 0x2AFF, "Supplemental Mathematical Operators" },
{ 0x2B00, 0x2BFF, "Miscellaneous Symbols and Arrows" },
{ 0x2C00, 0x2C5F, "Glagolitic" },
{ 0x2C60, 0x2C7F, "Latin Extended-C" },
{ 0x2C80, 0x2CFF, "Coptic" },
{ 0x2D00, 0x2D2F, "Georgian Supplement" },
{ 0x2D30, 0x2D7F, "Tifinagh" },
{ 0x2D80, 0x2DDF, "Ethiopic Extended" },
{ 0x2DE0, 0x2DFF, "Cyrillic Extended-A" },
{ 0x2E00, 0x2E7F, "Supplemental Punctuation" },
{ 0x2E80, 0x2EFF, "CJK Radicals Supplement" },
{ 0x2F00, 0x2FDF, "Kangxi Radicals" },
{ 0x2FF0, 0x2FFF, "Ideographic Description Characters" },
{ 0x3000, 0x303F, "CJK Symbols and Punctuation" },
{ 0x3040, 0x309F, "Hiragana" },
{ 0x30A0, 0x30FF, "Katakana" },
{ 0x3100, 0x312F, "Bopomofo" },
{ 0x3130, 0x318F, "Hangul Compatibility Jamo" },
{ 0x3190, 0x319F, "Kanbun" },
{ 0x31A0, 0x31BF, "Bopomofo Extended" },
{ 0x31C0, 0x31EF, "CJK Strokes" },
{ 0x31F0, 0x31FF, "Katakana Phonetic Extensions" },
{ 0x3200, 0x32FF, "Enclosed CJK Letters and Months" },
{ 0x3300, 0x33FF, "CJK Compatibility" },
{ 0x3400, 0x4DBF, "CJK Unified Ideographs Extension A" },
{ 0x4DC0, 0x4DFF, "Yijing Hexagram Symbols" },
{ 0x4E00, 0x9FFF, "CJK Unified Ideographs" },
{ 0xA000, 0xA48F, "Yi Syllables" },
{ 0xA490, 0xA4CF, "Yi Radicals" },
{ 0xA4D0, 0xA4FF, "Lisu" },
{ 0xA500, 0xA63F, "Vai" },
{ 0xA640, 0xA69F, "Cyrillic Extended-B" },
{ 0xA6A0, 0xA6FF, "Bamum" },
{ 0xA700, 0xA71F, "Modifier Tone Letters" },
{ 0xA720, 0xA7FF, "Latin Extended-D" },
{ 0xA800, 0xA82F, "Syloti Nagri" },
{ 0xA830, 0xA83F, "Common Indic Number Forms" },
{ 0xA840, 0xA87F, "Phags-pa" },
{ 0xA880, 0xA8DF, "Saurashtra" },
{ 0xA8E0, 0xA8FF, "Devanagari Extended" },
{ 0xA900, 0xA92F, "Kayah Li" },
{ 0xA930, 0xA95F, "Rejang" },
{ 0xA960, 0xA97F, "Hangul Jamo Extended-A" },
{ 0xA980, 0xA9DF, "Javanese" },
{ 0xA9E0, 0xA9FF, "Myanmar Extended-B" },
{ 0xAA00, 0xAA5F, "Cham" },
{ 0xAA60, 0xAA7F, "Myanmar Extended-A" },
{ 0xAA80, 0xAADF, "Tai Viet" },
{ 0xAAE0, 0xAAFF, "Meetei Mayek Extensions" },
{ 0xAB00, 0xAB2F, "Ethiopic Extended-A" },
{ 0xAB30, 0xAB6F, "Latin Extended-E" },
{ 0xAB70, 0xABBF, "Cherokee Supplement" },
{ 0xABC0, 0xABFF, "Meetei Mayek" },
{ 0xAC00, 0xD7AF, "Hangul Syllables" },
{ 0xD7B0, 0xD7FF, "Hangul Jamo Extended-B" },
{ 0xD800, 0xDB7F, "High Surrogates" },
{ 0xDB80, 0xDBFF, "High Private Use Surrogates" },
{ 0xDC00, 0xDFFF, "Low Surrogates" },
{ 0xE000, 0xF8FF, "Private Use Area" },
{ 0xF900, 0xFAFF, "CJK Compatibility Ideographs" },
{ 0xFB00, 0xFB4F, "Alphabetic Presentation Forms" },
{ 0xFB50, 0xFDFF, "Arabic Presentation Forms-A" },
{ 0xFE00, 0xFE0F, "Variation Selectors" },
{ 0xFE10, 0xFE1F, "Vertical Forms" },
{ 0xFE20, 0xFE2F, "Combining Half Marks" },
{ 0xFE30, 0xFE4F, "CJK Compatibility Forms" },
{ 0xFE50, 0xFE6F, "Small Form Variants" },
{ 0xFE70, 0xFEFF, "Arabic Presentation Forms-B" },
{ 0xFF00, 0xFFEF, "Halfwidth and Fullwidth Forms" },
{ 0xFFF0, 0xFFFF, "Specials" },
{ 0x10000, 0x1007F, "Linear B Syllabary" },
{ 0x10080, 0x100FF, "Linear B Ideograms" },
{ 0x10100, 0x1013F, "Aegean Numbers" },
{ 0x10140, 0x1018F, "Ancient Greek Numbers" },
{ 0x10190, 0x101CF, "Ancient Symbols" },
{ 0x101D0, 0x101FF, "Phaistos Disc" },
{ 0x10280, 0x1029F, "Lycian" },
{ 0x102A0, 0x102DF, "Carian" },
{ 0x102E0, 0x102FF, "Coptic Epact Numbers" },
{ 0x10300, 0x1032F, "Old Italic" },
{ 0x10330, 0x1034F, "Gothic" },
{ 0x10350, 0x1037F, "Old Permic" },
{ 0x10380, 0x1039F, "Ugaritic" },
{ 0x103A0, 0x103DF, "Old Persian" },
{ 0x10400, 0x1044F, "Deseret" },
{ 0x10450, 0x1047F, "Shavian" },
{ 0x10480, 0x104AF, "Osmanya" },
{ 0x104B0, 0x104FF, "Osage" },
{ 0x10500, 0x1052F, "Elbasan" },
{ 0x10530, 0x1056F, "Caucasian Albanian" },
{ 0x10600, 0x1077F, "Linear A" },
{ 0x10800, 0x1083F, "Cypriot Syllabary" },
{ 0x10840, 0x1085F, "Imperial Aramaic" },
{ 0x10860, 0x1087F, "Palmyrene" },
{ 0x10880, 0x108AF, "Nabataean" },
{ 0x108E0, 0x108FF, "Hatran" },
{ 0x10900, 0x1091F, "Phoenician" },
{ 0x10920, 0x1093F, "Lydian" },
{ 0x10980, 0x1099F, "Meroitic Hieroglyphs" },
{ 0x109A0, 0x109FF, "Meroitic Cursive" },
{ 0x10A00, 0x10A5F, "Kharoshthi" },
{ 0x10A60, 0x10A7F, "Old South Arabian" },
{ 0x10A80, 0x10A9F, "Old North Arabian" },
{ 0x10AC0, 0x10AFF, "Manichaean" },
{ 0x10B00, 0x10B3F, "Avestan" },
{ 0x10B40, 0x10B5F, "Inscriptional Parthian" },
{ 0x10B60, 0x10B7F, "Inscriptional Pahlavi" },
{ 0x10B80, 0x10BAF, "Psalter Pahlavi" },
{ 0x10C00, 0x10C4F, "Old Turkic" },
{ 0x10C80, 0x10CFF, "Old Hungarian" },
{ 0x10D00, 0x10D3F, "Hanifi Rohingya" },
{ 0x10E60, 0x10E7F, "Rumi Numeral Symbols" },
{ 0x10E80, 0x10EBF, "Yezidi" },
{ 0x10F00, 0x10F2F, "Old Sogdian" },
{ 0x10F30, 0x10F6F, "Sogdian" },
{ 0x10FB0, 0x10FDF , "Chorasmian" },
{ 0x10FE0, 0x10FFF, "Elymaic" },
{ 0x11000, 0x1107F, "Brahmi" },
{ 0x11080, 0x110CF, "Kaithi" },
{ 0x110D0, 0x110FF, "Sora Sompeng" },
{ 0x11100, 0x1114F, "Chakma" },
{ 0x11150, 0x1117F, "Mahajani" },
{ 0x11180, 0x111DF, "Sharada" },
{ 0x111E0, 0x111FF, "Sinhala Archaic Numbers" },
{ 0x11200, 0x1124F, "Khojki" },
{ 0x11280, 0x112AF, "Multani" },
{ 0x112B0, 0x112FF, "Khudawadi" },
{ 0x11300, 0x1137F, "Grantha" },
{ 0x11400, 0x1147F, "Newa" },
{ 0x11480, 0x114DF, "Tirhuta" },
{ 0x11580, 0x115FF, "Siddham" },
{ 0x11600, 0x1165F, "Modi" },
{ 0x11660, 0x1167F, "Mongolian Supplement" },
{ 0x11680, 0x116CF, "Takri" },
{ 0x11700, 0x1173F, "Ahom" },
{ 0x11800, 0x1184F, "Dogra" },
{ 0x118A0, 0x118FF, "Warang Citi" },
{ 0x11900, 0x1195F, "Dives Akuru" },
{ 0x119A0, 0x119FF, "Nandinagari" },
{ 0x11A00, 0x11A4F, "Zanabazar Square" },
{ 0x11A50, 0x11AAF, "Soyombo" },
{ 0x11AC0, 0x11AFF, "Pau Cin Hau" },
{ 0x11C00, 0x11C6F, "Bhaiksuki" },
{ 0x11C70, 0x11CBF, "Marchen" },
{ 0x11D00, 0x11D5F, "Masaram Gondi" },
{ 0x11D60, 0x11DAF, "Gunjala Gondi" },
{ 0x11EE0, 0x11EFF, "Makasar" },
{ 0x11FB0, 0x11FBF, "Lisu Supplement" },
{ 0x11FC0, 0x11FFF, "Tamil Supplement" },
{ 0x12000, 0x123FF, "Cuneiform" },
{ 0x12400, 0x1247F, "Cuneiform Numbers and Punctuation" },
{ 0x12480, 0x1254F, "Early Dynastic Cuneiform" },
{ 0x13000, 0x1342F, "Egyptian Hieroglyphs" },
{ 0x13430, 0x1343F, "Egyptian Hieroglyph Format Controls" },
{ 0x14400, 0x1467F, "Anatolian Hieroglyphs" },
{ 0x16800, 0x16A3F, "Bamum Supplement" },
{ 0x16A40, 0x16A6F, "Mro" },
{ 0x16AD0, 0x16AFF, "Bassa Vah" },
{ 0x16B00, 0x16B8F, "Pahawh Hmong" },
{ 0x16E40, 0x16E9F, "Medefaidrin" },
{ 0x16F00, 0x16F9F, "Miao" },
{ 0x16FE0, 0x16FFF, "Ideographic Symbols and Punctuation" },
{ 0x17000, 0x187FF, "Tangut" },
{ 0x18800, 0x18AFF, "Tangut Components" },
{ 0x18B00, 0x18CFF, "Khitan Small Script" },
{ 0x18D00, 0x18D8F, "Tangut Supplement" },
{ 0x1B000, 0x1B0FF, "Kana Supplement" },
{ 0x1B100, 0x1B12F, "Kana Extended-A" },
{ 0x1B130, 0x1B16F, "Small Kana Extension" },
{ 0x1B170, 0x1B2FF, "Nushu" },
{ 0x1BC00, 0x1BC9F, "Duployan" },
{ 0x1BCA0, 0x1BCAF, "Shorthand Format Controls" },
{ 0x1D000, 0x1D0FF, "Byzantine Musical Symbols" },
{ 0x1D100, 0x1D1FF, "Musical Symbols" },
{ 0x1D200, 0x1D24F, "Ancient Greek Musical Notation" },
{ 0x1D2E0, 0x1D2FF, "Mayan Numerals" },
{ 0x1D300, 0x1D35F, "Tai Xuan Jing Symbols" },
{ 0x1D360, 0x1D37F, "Counting Rod Numerals" },
{ 0x1D400, 0x1D7FF, "Mathematical Alphanumeric Symbols" },
{ 0x1D800, 0x1DAAF, "Sutton SignWriting" },
{ 0x1E000, 0x1E02F, "Glagolitic Supplement" },
{ 0x1E100, 0x1E14F, "Nyiakeng Puachue Hmong" },
{ 0x1E2C0, 0x1E2FF, "Wancho" },
{ 0x1E800, 0x1E8DF, "Mende Kikakui" },
{ 0x1E900, 0x1E95F, "Adlam" },
{ 0x1EC70, 0x1ECBF, "Indic Siyaq Numbers" },
{ 0x1ED00, 0x1ED4F, "Ottoman Siyaq Numbers" },
{ 0x1EE00, 0x1EEFF, "Arabic Mathematical Alphabetic Symbols" },
{ 0x1F000, 0x1F02F, "Mahjong Tiles" },
{ 0x1F030, 0x1F09F, "Domino Tiles" },
{ 0x1F0A0, 0x1F0FF, "Playing Cards" },
{ 0x1F100, 0x1F1FF, "Enclosed Alphanumeric Supplement" },
{ 0x1F200, 0x1F2FF, "Enclosed Ideographic Supplement" },
{ 0x1F300, 0x1F5FF, "Miscellaneous Symbols and Pictographs" },
{ 0x1F600, 0x1F64F, "Emoticons" },
{ 0x1F650, 0x1F67F, "Ornamental Dingbats" },
{ 0x1F680, 0x1F6FF, "Transport and Map Symbols" },
{ 0x1F700, 0x1F77F, "Alchemical Symbols" },
{ 0x1F780, 0x1F7FF, "Geometric Shapes Extended" },
{ 0x1F800, 0x1F8FF, "Supplemental Arrows-C" },
{ 0x1F900, 0x1F9FF, "Supplemental Symbols and Pictographs" },
{ 0x1FA00, 0x1FA6F, "Chess Symbols" },
{ 0x1FA70, 0x1FAFF, "Symbols and Pictographs Extended-A" },
{ 0x1FB00, 0x1FBFF, "Symbols for Legacy Computing" },
{ 0x20000, 0x2A6DF, "CJK Unified Ideographs Extension B" },
{ 0x2A700, 0x2B73F, "CJK Unified Ideographs Extension C" },
{ 0x2B740, 0x2B81F, "CJK Unified Ideographs Extension D" },
{ 0x2B820, 0x2CEAF, "CJK Unified Ideographs Extension E" },
{ 0x2CEB0, 0x2EBEF, "CJK Unified Ideographs Extension F" },
{ 0x2F800, 0x2FA1F, "CJK Compatibility Ideographs Supplement" },
{ 0x30000, 0x3134F, "CJK Unified Ideographs Extension G" },
{ 0xE0000, 0xE007F, "Tags" },
{ 0xE0100, 0xE01EF, "Variation Selectors Supplement" },
{ 0xF0000, 0xFFFFF, "Supplementary Private Use Area-A" },
{ 0x100000, 0x10FFFF, "Supplementary Private Use Area-B" },
};

static void PrintRanges(
    unsigned width, unsigned height,
    const unsigned char* bitmap_real,
    std::pair<unsigned,bool>(*find_real)(char32_t),
    const unsigned char* bitmap_fake,
    std::pair<unsigned,bool>(*find_fake)(char32_t))
{
    // start bitmap
    unsigned yc = 0, widest = 0, dfl_width = 64;
    std::vector<unsigned> pixels(dfl_width*width*(height+1));
    auto BitmapEndl = [&]() { ++yc; pixels.resize(dfl_width*width * ((height==5) ? 6 : height)*(yc+1)); };
    auto BitmapPrintCh = [&](unsigned xc, const unsigned char* bm, unsigned glyph, unsigned color)
    {
        unsigned hei = (height==5) ? 6 : height;
        unsigned bytes_per_row = (width+7)/8, bytes_per_char = bytes_per_row * height;
        if(xc+1 > widest) widest = xc+1;
        if(widest > dfl_width) fprintf(stderr, "xc=%u in font %ux%u\n", xc, width,height);
        bm += glyph * bytes_per_char;
        for(unsigned y=0; y<height; ++y)
        {
            unsigned widefont = bm[0];
            if(width >= 8)  {widefont |= (bm[1] << 8);
            if(width >= 16) {widefont |= (bm[2] << 16);
            if(width >= 24) {widefont |= (bm[3] << 24);}}}
            bm += bytes_per_row;

            unsigned* row = &pixels[((yc*hei + y) * dfl_width + xc) * width];
            for(unsigned x=0; x<width; ++x)
                if((widefont >> (width-1 - x)) & 1)
                    row[x] = color;
        }
    };
    unsigned bitmap_index = 0;
    auto BitmapFlush = [&]()
    {
        // end bitmap
        char buf[64];
        std::sprintf(buf, "coverage-%ux%u-%u.png", width,height, bitmap_index);
        std::FILE* fp = std::fopen((std::string("../doc/")+buf).c_str(), "wb");
        unsigned hei = (height==5) ? 6 : height;
        if(width <= 6)
        {
            gdImagePtr im = gdImageCreateTrueColor(widest*width*2, yc*hei*2);
            for(unsigned y=0; y<yc*hei*2; ++y)
                for(unsigned x=0; x<widest*width*2; ++x)
                    gdImageSetPixel(im, x,y, pixels[(y/2)*dfl_width*width + (x/2)]);
            gdImagePng(im, fp);
            gdImageDestroy(im);
        }
        else
        {
            gdImagePtr im = gdImageCreateTrueColor(widest*width, yc*hei);
            for(unsigned y=0; y<yc*hei; ++y)
                for(unsigned x=0; x<widest*width; ++x)
                    gdImageSetPixel(im, x,y, pixels[y*dfl_width*width + x]);
            gdImagePng(im, fp);
            gdImageDestroy(im);
        }
        std::fclose(fp);

        std::cout << "![Font "<<width<<'x'<<height<<" coverage](" << buf << ")\n";
        ++bitmap_index;
        yc = 0; widest = 0;
        pixels.clear(); pixels.resize(dfl_width*width*hei);
    };

    bool title_printed = false;
    for(auto [begin,end,name]: blocks)
    {
        if(title_printed) { title_printed = false; BitmapEndl(); }
        unsigned span = 32;
        if(begin == 0xAC00)
        {
            span = 28;
        }
        for(unsigned index=begin; index<end; index+=span)
        {
            unsigned long ok1 = 0, ok2 = 0;
            for(unsigned p=0; p<span; ++p)
            {
                if(index+p <= end && find_real(index+p).second) ok1 |= 1ul<<p;
                if(index+p <= end && find_fake(index+p).second) ok2 |= 1ul<<p;
            }
            if(ok1 || ok2)
            {
                if(!title_printed)
                {
                    if(yc*height >= 600)
                    {
                        BitmapFlush();
                    }
                    title_printed = true;
                    unsigned x=0;
                    for(char c: name)
                        BitmapPrintCh(x++, bitmap_real, find_real(c).first, 0xFFFFFF);
                    BitmapEndl();
                    BitmapEndl();
                }
                else
                {
                    if(yc*height >= 1024)
                    {
                        BitmapFlush();
                    }
                }
                char buf[32];
                std::sprintf(buf, "U+%04X..U+%04X ", index, std::min(index+span-1, end));
                std::u32string str = FromUTF8(buf);
                unsigned color_start = str.size();
                for(unsigned p=0; p<span; ++p)
                    if((ok1|ok2) & (1u << p))
                        str += char32_t(index+p);
                    else
                        str += isdouble(index+p) ? char32_t(0x3000) : U' ';
                str += U' ';

                for(std::size_t p=0; p<str.size(); ++p)
                {
                    if(p < color_start)
                        BitmapPrintCh(p, bitmap_real, find_real(str[p]).first, 0xFFFFFF);
                    else if(ok1 & (1u << (p-color_start)))
                        BitmapPrintCh(p, bitmap_real, find_real(str[p]).first, 0xFFFAF2);
                    else
                        BitmapPrintCh(p, bitmap_fake, find_fake(str[p]).first, 0xBB7733);
                }
                BitmapEndl();
            }
        }
    }
    BitmapFlush();
}

static const std::map<unsigned,std::string> lore
{
    {4*256+5, R"(
X11 font “micro”. For clarity, this font is pictured as 4x6 on this page
by inserting a blank pixel line below every character, but the font is
really 4x5. This means that capital letters on adjacent lines are touching.

Besides the full ASCII, this font includes an odd set of special characters,
including ẍ, some Greek symbols, logical operators, and the APL asterisk
with diearesis that I have never seen used anywhere, for a total of 128
glyphs.
)"},
    {4*256+6, "X11 misc-fixed font `-misc-fixed-medium-r-normal--6-60-75-75-c-40-iso10646-1`."},
    {5*256+7, "X11 misc-fixed font `-misc-fixed-medium-r-normal--7-70-75-75-c-50-iso10646-1`."},
    {5*256+8, "X11 misc-fixed font `-misc-fixed-medium-r-normal--8-80-75-75-c-50-iso10646-1`."},
    {6*256+9, "X11 misc-fixed font `-misc-fixed-medium-r-normal--9-90-75-75-c-60-iso10646-1`."},
    {6*256+10, "X11 misc-fixed font `-misc-fixed-medium-r-normal--10-100-75-75-c-60-iso10646-1`."},
    {6*256+12, "X11 misc-fixed font `-misc-fixed-medium-r-semicondensed--12-110-75-75-c-60-iso10646-1`."},
    {6*256+13, "X11 misc-fixed font `-misc-fixed-bold-r-semicondensed--13-120-75-75-c-60-iso10646-1`. Pairs perfectly with 12x13."},
    {7*256+13, "X11 misc-fixed font `-misc-fixed-bold-r-normal--13-120-75-75-c-70-iso10646-1`."},
    {7*256+14, "X11 misc-fixed font `-misc-fixed-bold-r-normal--14-130-75-75-c-70-iso10646-1`."},
    {8*256+13, "X11 misc-fixed font `-misc-fixed-bold-r-normal--13-120-75-75-c-80-iso10646-1`."},
    {9*256+15, "X11 misc-fixed font `-misc-fixed-bold-r-normal--15-140-75-75-c-90-iso10646-1`."},
    {9*256+18, "X11 misc-fixed font `-misc-fixed-bold-r-normal--18-120-100-100-c-90-iso10646-1`. Pairs perfectly with 18x18."},
    {10*256+20, "X11 misc-fixed font `-misc-fixed-medium-r-normal--20-200-75-75-c-100-iso10646-1`."},
    {12*256+13, "X11 misc-fixed font `-misc-fixed-medium-r-normal-ja-13-120-75-75-c-120-iso10646-1` (Japanese)."},
    {18*256+18, "X11 misc-fixed fonts `-misc-fixed-medium-r-normal-ja-18-120-100-100-c-180-iso10646-1` (Japanese) and `-misc-fixed-medium-r-normal-ko-18-120-100-100-c-180-iso10646-1` (Korean)."},
    {8*256+8, R"(
* VGA ROM BIOS font (codepage 437)
* DISPLAY.SYS codepage 850
* DISPLAY.SYS codepage 852
* cp857-8x8.psf.gz (Linux consolefonts)
* iso03.f08.psf.gz, iso04.f08.psf.gz, iso05.f08.psf.gz, iso06.f08.psf.gz, iso07.f08.psf.gz, iso08.f08.psf.gz, lat9-08.psf.gz
)"},
    {8*256+10, R"(
* 8x10 Source unknown (possibly created automatically by resizing 8x12)
* lat1-10.psf.gz, lat2-10.psf.gz, lat4-10.psf.gz, lat9-10.psf.gz (Linux consolefonts)
)"},
    {8*256+12, R"(
* 8x12 Source unknown (possibly created automatically by resizing 8x14)
* lat1-10.psf.gz, lat2-10.psf.gz, lat4-10.psf.gz, lat9-10.psf.gz (Linux consolefonts)
)"},
    {8*256+14, R"(
* VGA ROM BIOS font (codepage 437)
* DISPLAY.SYS codepage 850
* DISPLAY.SYS codepage 852
* cp857-8x14.psf.gz (Linux consolefonts)
* iso03.f14.psf.gz, iso04.f14.psf.gz, iso05.f14.psf.gz, iso06.f14.psf.gz, iso07.f14.psf.gz, iso08.f14.psf.gz, lat9-14.psf.gz
)"},
    {8*256+15, R"(
* 8x15 source unknown (possibly created automatically by resizing 8x16)
)"},
    {8*256+16, R"(
* VGA ROM BIOS font (codepage 437)
* DISPLAY.SYS codepage 850
* DISPLAY.SYS codepage 852
* cp857-8x16.psf.gz (Linux consolefonts)
* iso03.f16.psf.gz, iso04.f16.psf.gz, iso05.f16.psf.gz, iso06.f16.psf.gz, iso07.f16.psf.gz, iso08.f16.psf.gz, lat9-16.psf.gz
)"},
    {8*256+19, "vga8x19.bdf by Martin Reuber, based on VGA ROM BIOS font"},
};
int main()
{
    for(auto p: lore)
    {
        unsigned x = p.first / 256, y = p.first % 256;
        std::cout << "\n## Font " << x << 'x' << y << "\n\n" << p.second
                     << "\n\n";
        const auto& entry1 = authentic::fonts.find(p.first)->second;
        const auto& entry2 = pseudo::fonts.find(p.first)->second;
        PrintRanges(x,y,
                    entry1.first, entry1.second,
                    entry2.first, entry2.second);
    }
}
 