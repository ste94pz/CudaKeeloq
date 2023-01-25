#include "keeloq_kernel_input.h"
#include "common.h"

void KeeloqKernelInput::WriteDecryptors(const std::vector<Decryptor>& source, size_t from, size_t num)
{
	if (decryptors != nullptr)
	{
		assert(generator.type == BruteforceType::Dictionary);

		size_t copy_num = std::max(0ull, std::min(num, (source.size() - from)));
		decryptors->write(&source[from], copy_num);
	}
}


void KeeloqKernelInput::NextDecryptor()
{
	assert(generator.type != BruteforceType::Dictionary);
	generator.next_decryptor();
}