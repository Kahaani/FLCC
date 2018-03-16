//===------------------------------------------------===//
// Fan-chieh Lower Character Connector 20171229 V6.2.24
// Producer: Chrome <chromezh@outlook.com>
//===------------------------------------------------===//

#define VERSION "20171229 V6.2.24"

#include <vector>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <windows.h>
#include <string>

#include <utility>

// Beginning of module cblock

class cblock
{
public:
    std::vector <std::vector <std::string>> run(const std::vector <std::pair <std::string, std::string>> &strpair);
private:
    std::vector <std::string> regist;
    std::vector <size_t> chief;
    size_t reg(std::string key) noexcept;
    size_t getChief(size_t i) noexcept;
    void setChief(size_t i, size_t target) noexcept;
    void connect(size_t a, size_t b) noexcept;
};

/** Returns the number of a certain key in vector regist. If the key was not
 *  found in the vector regist, than the key will be registed, and then return
 *  the number of that key.
 */
size_t cblock::reg(std::string key) noexcept
{
    size_t i;
    for(i = 0; i < regist.size(); i++) if(regist[i] == key) break;  // Find the number of key in vector regist

    if(i == regist.size())  // If not found
    {
        regist.push_back(key);  // Regist a new string
        chief.push_back(i);
    }
    return i;
}

/** Find the greatest chief. */
size_t cblock::getChief(size_t i) noexcept
{
    size_t c;
    for(c = chief[i]; c != chief[c]; c = chief[c]);
    return c;
}

/** Set all the chiefs of target to n. */
void cblock::setChief(size_t target, size_t n) noexcept
{
    size_t chiefAhead;
    for(;;)
    {
        chiefAhead = chief[target];
        chief[target] = n;
        if(chiefAhead == target) break;
        target = chiefAhead;
    }
}

void cblock::connect(size_t a, size_t b) noexcept
{
    size_t chief_a = getChief(a), chief_b = getChief(b);
    if(chief_a < chief_b) setChief(b, chief_a);
    else if(chief_a > chief_b) setChief(a, chief_b);
}

std::vector <std::vector <std::string>> cblock::run(const std::vector <std::pair <std::string, std::string>> &strpair)
{
    for(const std::pair <std::string, std::string> it: strpair)
    {
        size_t strleft = reg(it.first), strright = reg(it.second);
        connect(strleft, strright);
    }

    // countCluster
    std::vector <std::vector <std::string>> result;
    {
        std::vector <size_t> chiefRegister;
        for(size_t i = 0; i < chief.size(); i++)
        {
            if(i == chief[i])
            {
                result.push_back(std::vector <std::string> ());
                size_t insertPos = chiefRegister.size();
                chiefRegister.push_back(i);
                result[insertPos].push_back(regist[i]);
            }
            else
            {
                size_t clusterCount;
                for(clusterCount = 0; chiefRegister[clusterCount] != getChief(i); clusterCount++);
                result[clusterCount].push_back(regist[i]);
            }
        }
    }

    // Cleaning
    regist.clear();
    chief.clear();

    return result;
}

// End of module cblock

/** Open a c-file. */
void fileopen(FILE *&fp, const char *filename, const char *mode)
{
    if(!(fp = fopen(filename, mode)))
    {
        fprintf(stderr, "Error: Cannot open file %s in mode %s.\n", filename, mode);
        exit(-1);
    }
}

/** Return the size of a c-style string. */
size_t strsize(const char *str)
{
    return strlen(str)+1;
}

/** Check if c-style string str1 and str2 is equal. */
bool strequ(const char *str1, const char *str2)
{
    return strcmp(str1, str2) == 0;
}

const char *arabic2chinese(int n)
{
    switch(n)
    {
    case 0: return u8"零";
    case 1: return u8"一";
    case 2: return u8"二";
    case 3: return u8"三";
    case 4: return u8"四";
    case 5: return u8"五";
    case 6: return u8"六";
    case 7: return u8"七";
    default:
        fprintf(stderr, "Error: Numeric value too large.\n");
        exit(-2);
    }
}

/** Free every element that the pointer in the vector points to,
  * but will not delete the pointers vector itself.
  */
template <class tp> void freevector(std::vector <tp> &v) noexcept
{
    for(tp it: v) free(it);
}

/** Check if a certain element is contained in the container. */
bool appear(const std::vector <char *> &c, const char *e) noexcept
{
    for(const char *it: c) if(strcmp(it, e) == 0) return true;
    return false;
}

/** Count the number of rhymes in the file and make a record. */
std::vector <char *> rhymeCount(FILE *finp) noexcept
{
    std::vector <char *> rhymeList;
    char rhymeText[32];
    while(fscanf(finp, "%31[^\t]%*[^\n]\n", rhymeText) == 1)
    {
        if(!appear(rhymeList, rhymeText))
        {
            char *p = static_cast <char *> (malloc(strsize(rhymeText)*sizeof(char)));
            strcpy(p, rhymeText);
            rhymeList.push_back(p);
        }
    }
    rewind(finp);
    return rhymeList;
}

/** Count the number of lower chars in designated rhyme in the file and make a record. */
std::vector <char *> lowerCharCount(FILE *finp, const char *rhymeName) noexcept
{
    std::vector <char *> lowerCharList;
    char rhymeText[32], lowerCharText[32];
    while(fscanf(finp, "%31[^\t]\t%*[^\t]\t%*[^\t]\t%31[^\n]\n", rhymeText, lowerCharText) == 2)
    {
        if(strequ(rhymeText, rhymeName) && !appear(lowerCharList, lowerCharText))
        {
            char *p = static_cast <char *> (malloc(strsize(lowerCharText)*sizeof(char)));
            strcpy(p, lowerCharText);
            lowerCharList.push_back(p);
        }
    }
    rewind(finp);
    return lowerCharList;
}

/** Count the occurance times of a designed lower char in designated rhyme in the file. */
size_t lowerCharOccuranceTime(
    FILE *finp,
    const char *rhymeName,
    const char *lowerCharName) noexcept
{
    size_t t = 0;
    std::vector <char *> smallRimeRegister;
    char rhymeText[32], smallRimeText[32], lowerCharText[32];
    while(fscanf(finp, "%31[^\t]\t%31[^\t]\t%*[^\t]\t%31[^\n]\n", rhymeText, smallRimeText, lowerCharText) == 3)
    {
        if(strequ(rhymeText, rhymeName) &&
           strequ(lowerCharText, lowerCharName) &&
           !appear(smallRimeRegister, smallRimeText))
        {
            char *p = static_cast <char *> (malloc(strsize(smallRimeText)*sizeof(char)));
            strcpy(p, smallRimeText);
            smallRimeRegister.push_back(p);
            t++;
        }
    }
    freevector(smallRimeRegister);  // Free memory
    rewind(finp);
    return t;
}

/** Count the occurance times of lower chars in designated rhyme in the file and make a record. */
std::vector <size_t> lowerCharOccuranceCount(
    FILE *finp,
    const char *rhymeName,
    const std::vector <char *> &lowerCharList) noexcept
{
    std::vector <size_t> lowerCharOccuranceList;
    for(const char *it: lowerCharList)  // For each lower char
    {
        lowerCharOccuranceList.push_back(lowerCharOccuranceTime(finp, rhymeName, it));
    }
    return lowerCharOccuranceList;
}

/** Find the rhymes that a char occurs. */
std::string findCharOccuranceRhyme(FILE *finp, const char *charName)
{
    char rhymeText[32], charText[32];
    std::string result;
    while(fscanf(finp, "%31[^\t]\t%*[^\t]\t%31[^\t]\t%*[^\n]\n", rhymeText, charText) == 2)
    {
        if(strequ(charText, charName))
        {
            if(result.size() > 0) result += u8"、";
            result += rhymeText;
        }
    }
    rewind(finp);
    return result;
}

/** Find the lower char of a lower char in designated rhyme in the file.
  * If the lower char could not be found, a warning would be sent instead.
  */
char *lowerCharQuery(FILE *finp, const char *rhymeName, const char *lowerCharName) noexcept
{
    char rhymeText[32], charText[32], lowerCharText[32];
    bool find = false;
    while(fscanf(finp, "%31[^\t]\t%*[^\t]\t%31[^\t]\t%31[^\n]\n", rhymeText, charText, lowerCharText) == 3)
    {
        if(strequ(rhymeText, rhymeName) && strequ(charText, lowerCharName))
        {
            find = true;
            break;
        }
    }
    rewind(finp);
    if(find)
    {
        return strcpy(static_cast <char *> (malloc(strsize(lowerCharText)*sizeof(char))), lowerCharText);
    }
    else
    {
        char tmp[128];
        std::string alterLowerChar = findCharOccuranceRhyme(finp, lowerCharName);
        if(alterLowerChar == "") sprintf(tmp, u8"下字不存在");
        else sprintf(tmp, u8"下字在%s", alterLowerChar.c_str());
        return strcpy(static_cast <char *> (malloc(strsize(tmp)*sizeof(char))), tmp);
    }
}

/** Find the lower chars of lower chars in designated rhyme in the file and make a record. */
std::vector <char *> lowerCharOfLowerCharCount(
        FILE *finp,
        const char *rhymeName,
        const std::vector <char *> &lowerCharList) noexcept
{
    std::vector <char *> lowerCharOfLowerCharList;
    for(const char *it: lowerCharList)  // For each lower char
    {
        lowerCharOfLowerCharList.push_back(lowerCharQuery(finp, rhymeName, it));
    }
    return lowerCharOfLowerCharList;
}

/** Find the element which is the same as key in vector def, and return
  * the element in vector im which has the same index as the element found.
  */
size_t pairmap(const std::vector <char *> &def, const std::vector <size_t> &im, const char *key) noexcept
{
    size_t i;
    for(i = 0; i < def.size(); i++) if(strequ(def[i], key)) return im[i];
    return 0;
}

char *pairmap(const std::vector <char *> &def, const std::vector <char *> &im, const char *key) noexcept
{
    size_t i;
    for(i = 0; i < def.size(); i++) if(strequ(def[i], key)) return im[i];
    return nullptr;
}

size_t file_size(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t fsize = static_cast <size_t> (ftell(fp));
    rewind(fp);
    return fsize;
}

/** Connect a rhyme according to its name. */
void connectRhyme(FILE *finp, FILE *foutp, const char *rhyme)
{
    std::vector <char *> lowerCharList = lowerCharCount(finp, rhyme);  // Count the number of lower chars

    std::vector <size_t> lowerCharOccuranceList = lowerCharOccuranceCount(finp, rhyme, lowerCharList);
        // Count the occurance times of lower chars
    std::vector <char *> lowerCharOfLowerCharList = lowerCharOfLowerCharCount(finp, rhyme, lowerCharList);
        // Find the lower chars of lower chars

    std::vector <std::pair <std::string, std::string>> lowerCharPair;
    for(size_t i = 0; i < lowerCharList.size(); i++) // Make pairs
    {
        lowerCharPair.push_back(std::make_pair(lowerCharList[i], lowerCharOfLowerCharList[i]));
    }

    cblock c;
    std::vector <std::vector <std::string>> res = c.run(lowerCharPair);
    printf(u8"\n%s 共%s類\n", rhyme, arabic2chinese(static_cast <int> (res.size())));
    fprintf(foutp, u8"\n%s 共%s類\n", rhyme, arabic2chinese(static_cast <int> (res.size())));
    for(const std::vector <std::string> it: res)
    {
        for(const std::string it2: it)
        {
            const char *lowerCharOutput = pairmap(lowerCharList, lowerCharOfLowerCharList, it2.c_str());
            if(lowerCharOutput)
            {
                size_t lowerCharOccuranceOutput = pairmap(lowerCharList, lowerCharOccuranceList, it2.c_str());
                printf(u8"%s（%s）%llu ", it2.c_str(), lowerCharOutput, lowerCharOccuranceOutput);
                fprintf(foutp, u8"%s（%s）%llu ", it2.c_str(), lowerCharOutput, lowerCharOccuranceOutput);
            }
        }
        putchar('\n');
        fputc('\n', foutp);
    }

    freevector(lowerCharOfLowerCharList);
    freevector(lowerCharList);
    fflush(foutp);
}

int main()
{
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);

    system("chcp 65001");  // Change the code page to UTF-8 to prevent mojibake
    system("cls");

    FILE *finp;
    fileopen(finp, "input.txt", "r");

    FILE *foutp;
    char outFileName[32];
    sprintf(outFileName, "output_%4d%02d%02d%02d%02d%02d.txt",
        sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
    fileopen(foutp, outFileName, "w");

    printf(u8"反切下字系聯程序 " VERSION " 系聯報告\n");
    fprintf(foutp, u8"反切下字系聯程序 " VERSION " 系聯報告\n");

    printf(u8"系聯時間 %4d/%02d/%02d %02d:%02d:%02d\n",
        sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
    fprintf(foutp, u8"系聯時間 %4d/%02d/%02d %02d:%02d:%02d\n",
        sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

    std::vector <char *> rhymeList = rhymeCount(finp);  // Count the number of rhymes

    for(const char *it: rhymeList) connectRhyme(finp, foutp, it);  // Connect each rhyme

    freevector(rhymeList);
    fclose(finp);
    fclose(foutp);

    printf(u8"系聯成功，請在 output.txt 中查看結果。\n");
    system("PAUSE");
    return 0;
}
