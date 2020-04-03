#include <gtest/gtest.h>
#include "ConvertColorSpace.hpp"

/**
 * @brief Stringify a string macro (Used to stringify the path parset from cmake)
 * 
 */
#define stringify(a) #a
#define xstr(a) stringify(a)
class ConvertColorSpaceTest : public ::testing::Test
{
protected:
    /**
    * @brief Construct a new Convert Color Space Test object
    * 
    */
    ConvertColorSpaceTest() = default;

    /**
    * @brief Destroy the Convert Color Space Test object
    * 
    */
    ~ConvertColorSpaceTest() = default;

    /**
    * @brief Set the Up object
    * 
    */
    void SetUp() override{
        
    };

    /**
    * @brief Tear Down object
    * 
    */
    void TearDown() override{
        ccs.~ConvertColorSpace();
    };

    /**
    * @brief ConvertColorSpace Object
    * 
    */
    ConvertColorSpace ccs;

    /**
     * @brief Get the Path object
     * 
     * @return const std::string 
     */
    const std::string getPath(){
        return std::string(getRootPath())+"/test/test_files/pots.jpg";
    }

    /**
     * @brief Get the Root Path object
     * 
     * @return const std::string 
     */
    const std::string getRootPath(void)
    {
        return std::string(xstr(ROOT_PATH));
    }
};