#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "hash-library/hmac.h"
#include "hash-library/sha1.h"

static bool s_IsFinished = false;

std::string IntToString(int val);
std::string IntToByteArray(uint64_t val);
std::string GenerateTOTP(uint64_t unixTime);
std::string HexStringToByteArray(const std::string& hexString);


int main()
{
	std::cout << "Press Enter to stop.\n";
	std::thread thread([]() 
	{
		using namespace std::literals::chrono_literals;

		uint64_t unixTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		std::string totpCode = GenerateTOTP(unixTime);

		while (!s_IsFinished)
		{
			unixTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			
			if ((unixTime % 30) == 0)
				totpCode = GenerateTOTP(unixTime);

			printf("\rTime remaining = %2llu  TOTP = %s", 30 - (unixTime % 30), totpCode.c_str());
			std::this_thread::sleep_for(1s);
		}
	});

	std::cin.get();
	s_IsFinished = true;
	thread.join();
}

std::string GenerateTOTP(uint64_t unixTime)
{
	// TODO: use base32 decoder
	const std::string key = "s8Jpkm*aN.7!IOlgu!Eo2pq>0o;Aa.P!"; // base32 = "OM4EU4DLNUVGCTROG4QUST3MM52SCRLPGJYHCPRQN45UCYJOKAQQ"
	uint64_t unixTimestep = unixTime / 30;

	std::string unixTimestepBytes = IntToByteArray(unixTimestep);
	std::string sha1Hmac  = hmac<SHA1>(unixTimestepBytes, key);
	std::string hashBytes = HexStringToByteArray(sha1Hmac);

	int offset = hashBytes[hashBytes.length() - 1] & 0xf;
	int rHex   = (hashBytes[offset    ] & 0x7f) << 24 | 
				 (hashBytes[offset + 1] & 0xff) << 16 | 
				 (hashBytes[offset + 2] & 0xff) <<  8 | 
				 (hashBytes[offset + 3] & 0xff);

	return IntToString(rHex % 1000000);
}

std::string IntToByteArray(uint64_t val)
{
	std::string byteArray{"00000000"};

	for (int i = 7; i >= 0; i--)
	{
		byteArray[i] = val & 0xff;
		val >>= 8;
	}

	return byteArray;
}

std::string HexStringToByteArray(const std::string& hexString)
{
	std::string byteArray{};
	byteArray.reserve(hexString.length() / 2);

	for (int i = 0; i < hexString.length(); i += 2)
	{
		char first  = '\0';
		char second = '\0';

		if (hexString[i] >= '0' && hexString[i] <= '9')
			first = hexString[i] - '0';
		else if (hexString[i] >= 'a' && hexString[i] <= 'f')
			first = hexString[i] - 'a' + 10;

		if (hexString[i + 1] >= '0' && hexString[i + 1] <= '9')
			second = hexString[i + 1] - '0';
		else if (hexString[i + 1] >= 'a' && hexString[i + 1] <= 'f')
			second = hexString[i + 1] - 'a' + 10;
		
		byteArray += first * 16 + second;
	}

	return byteArray;
}

std::string IntToString(int val)
{
	std::string str{"000000"};
	int i = 5;
	while (val)
	{
		int rem = val % 10;
		val /= 10;
		str[i--] = char(rem) + '0';
	}
	return str;
}