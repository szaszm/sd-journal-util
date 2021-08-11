# sd-journal-util

	$ git clone git@github.com:szaszm/sd-journal-util.git
	$ cd sd-journal-util/
	$ mkdir build
	$ cd build
	$ conan install ..
	$ cmake -G Ninja ..
	$ ninja -v
	$ bin/sd_journal_cat
	
# Licensing

This is under the Unlicense, which is basically a do-whatever-you-want license. The code was an early experimentation that led to the implementation of the ConsumeJournald processor in [MiNiFi C++](https://github.com/apache/nifi-minifi-cpp/blob/main/extensions/systemd/ConsumeJournald.cpp). If you want to reuse parts of that work, you can also choose to do so under the Unlicense as long as you can verify that the copyright of all of the parts you're using is mine. This is the case for the whole file at the time of writing this.
