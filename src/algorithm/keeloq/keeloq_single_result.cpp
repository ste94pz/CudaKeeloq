#include "keeloq_single_result.h"

#include <stdio.h>

#include "device/cuda_common.h"

void SingleResult::DecryptedArray::print(uint8_t element, uint64_t ota, bool ismatch) const
{
    printf("[%-40s] Btn:0x%X\tSerial:0x%" PRIX32 "\tCounter:0x%X\t%s\n", KeeloqLearningType::Name(element),
        (ota >> 32) & 0xF,      // Button
        ota >> 36,              // Serial
        data[element] & 0xFFFF, // Counter
        (ismatch ? "(MATCH)" : ""));
}

void SingleResult::DecryptedArray::print() const
{
    for (uint8_t i = 0; i < ResultsCount; ++i)
    {
        print(i, -1, false);
    }
}

void SingleResult::print(bool onlymatch /* = true */) const
{
    printf("Results (Input: 0x%" PRIX64 " - Man key: 0x%" PRIX64 " - Seed: 0x%X )\n\n",
        encrypted.ota, decryptor.man(), decryptor.seed());

    for (uint8_t i = 0; i < ResultsCount; ++i)
    {
        bool isMatch = match == i;
        if (!onlymatch)
        {
            decrypted.print(i, encrypted.ota, isMatch);
        }
        else if (isMatch)
        {
            decrypted.print(i, encrypted.ota, isMatch);
        }
    }
    printf("\n");
}