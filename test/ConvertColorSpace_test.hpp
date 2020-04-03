#include <gtest/gtest.h>
#include "ConvertColorSpace.hpp"

class ConvertColorSpaceTest : public ::testing::Test
{
    protected:
        
        /**
         * @brief Construct a new Convert Color Space Test object
         * 
         */
        ConvertColorSpaceTest() =default;

        /**
         * @brief Destroy the Convert Color Space Test object
         * 
         */
        ~ConvertColorSpaceTest() =default;

        /**
         * @brief Set the Up object
         * 
         */
        void SetUp() override
        {

        };

        /**
         * @brief Tear Down object
         * 
         */
        void TearDown() override
        {

        };

        /**
         * @brief ConvertColorSpace Object
         * 
         */
        ConvertColorSpace ccs;
    
};