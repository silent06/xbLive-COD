#pragma once

class IniParse {
public:
	IniParse() { bIsGood = false; }

	IniParse(const char* pFileName) {
		bIsGood = false;
		auto file = fopen(pFileName, StrEnc("r"));
		if (file) {
			bIsGood = true;
			string currentSection;
			int currentLine = 0;
			char currentDilem = '=';

			char line[300];
			while (fgets(line, 300, file) != 0) {
				string strLine(line);
				strLine.erase(std::remove(strLine.begin(), strLine.end(), '\n'), strLine.end());
				if (strLine.empty()) continue;

				if (line[0] == ';') continue;

				currentLine++;
				currentDilem = '=';
				bool checkedDilem = false;

				if (line[0] == '[') {
					// section line
					currentSection = strLine;
					currentSection.erase(std::remove(currentSection.begin(), currentSection.end(), '['), currentSection.end());
					currentSection.erase(std::remove(currentSection.begin(), currentSection.end(), ']'), currentSection.end());

					if (currentSection.length() > 0) {
						if (currentSection[currentSection.length() - 1] == ' ') {
							currentSection[currentSection.length() - 1] = 0x0;
						}
					}
				} else {
					if (line[0] == NULL) {
						continue;
					}

					if (currentSection.c_str()) {
						bool isSpacedLeft = false;
						bool isSpacedRight = false;

					jStart:
						int equals = strLine.find(currentDilem);
						if (equals > 0) {
							if (line[equals - 1] == ' ') {
								isSpacedLeft = true;
							}

							if (line[equals + 1] == ' ') {
								isSpacedRight = true;
							}

							string key = strLine.substr(0, equals - (isSpacedLeft ? 1 : 0));
							string value = strLine.substr(equals + (isSpacedRight ? 2 : 1));

							if (value.length() <= 0) {
								continue;
							}

							if (value[value.length() - 1] == ' ')
								value[value.length() - 1] = 0x0;

							ItemMap.insert(make_pair(make_pair(currentSection, key), value));
						} else {
							if (strLine.find(':') > 0) {
								if (checkedDilem) continue;
								checkedDilem = true;

								currentDilem = ':';
								goto jStart;
							}
						}
					}
				}
			}

			fclose(file);
		}
	}

	vector<string> GetKeys() {
		vector<string> mapped;

		for (auto outer = ItemMap.begin(); outer != ItemMap.end(); ++outer) {
			mapped.push_back(outer->first.second);
		}

		return mapped;
	}

	vector<string> GetSections() {
		vector<string> mapped;

		for (auto outer = ItemMap.begin(); outer != ItemMap.end(); ++outer) {
			auto vit = Find(mapped, outer->first.first);
			if (!vit) {
				mapped.push_back(outer->first.first);
			}
		}

		return mapped;
	}

	vector<pair<string, string>> GetDataFromSection(const char* pSection) {
		vector<pair<string, string>> mapped;

		for (auto outer = ItemMap.begin(); outer != ItemMap.end(); ++outer) {
			if (!strcmp(outer->first.first.c_str(), pSection)) {
				mapped.push_back(make_pair(outer->first.second, outer->second));
			}
		}

		return mapped;
	}

	int ReadInt(const char* pSection, const char* pWhat, int defaultVal) {
		if (!ItemMap[make_pair(pSection, pWhat)].empty()) {
			return stoi(ItemMap[make_pair(pSection, pWhat)].c_str());
		}

		return defaultVal;
	}

	const char* ReadString(const char* pSection, const char* pWhat, const char* defaultVal) {
		if (!ItemMap[make_pair(pSection, pWhat)].empty()) {
			return ItemMap[make_pair(pSection, pWhat)].c_str();
		}

		return defaultVal;
	}

	float ReadFloat(const char* pSection, const char* pWhat, float defaultVal) {
		if (!ItemMap[make_pair(pSection, pWhat)].empty()) {
			return atof(ItemMap[make_pair(pSection, pWhat)].c_str());
		}

		return defaultVal;
	}

	bool ReadBool(const char* pSection, const char* pWhat, bool def) {
		if (!ItemMap[make_pair(pSection, pWhat)].empty()) {
			const char* ret = ItemMap[make_pair(pSection, pWhat)].c_str();

			if (strstr(ret, StrEnc("yes")) || strstr(ret, StrEnc("YES"))
				|| strstr(ret, StrEnc("true")) || strstr(ret, StrEnc("TRUE"))
				|| strstr(ret, StrEnc("1"))) {
				return true;
			}

			return false;
		}

		return def;
	}

	void ReadToggleInt(const char* pSection, const char* pWhat, bool* pOutBool, int* pOutInt, bool defaultBool = false, int defaultInt = 0) {
		if (!ItemMap[make_pair(pSection, pWhat)].empty()) {
			vector<string> splitVals;
			pUtils.Split(ItemMap[make_pair(pSection, pWhat)], ',', splitVals);

			// FORMAT: true,12 - bool, int
			if (splitVals.size() == 2) {
				if (strstr(splitVals[0].c_str(), "yes") || strstr(splitVals[0].c_str(), "YES")
					|| strstr(splitVals[0].c_str(), "true") || strstr(splitVals[0].c_str(), "TRUE")
					|| strstr(splitVals[0].c_str(), "1")) {
					*pOutBool = true;
				}

				*pOutInt = stoi(splitVals[1].c_str());
				return;
			}
		}

		*pOutBool = defaultBool;
		*pOutInt = defaultInt;
	}

	void ReadToggleFloat(const char* pSection, const char* pWhat, bool* pOutBool, float* pOutFloat, bool defaultBool = false, float defaultFloat = 0.f) {
		if (!ItemMap[make_pair(pSection, pWhat)].empty()) {
			vector<string> splitVals;
			pUtils.Split(ItemMap[make_pair(pSection, pWhat)], ',', splitVals);

			// FORMAT: true,12.121 - bool, float
			if (splitVals.size() == 2) {
				if (strstr(splitVals[0].c_str(), "yes") || strstr(splitVals[0].c_str(), "YES")
					|| strstr(splitVals[0].c_str(), "true") || strstr(splitVals[0].c_str(), "TRUE")
					|| strstr(splitVals[0].c_str(), "1")) {
					*pOutBool = true;
				}

				*pOutFloat = atof(splitVals[1].c_str());
				return;
			}
		}

		*pOutBool = defaultBool;
		*pOutFloat = defaultFloat;
	}

	Color ReadColor(const char* pSection, const char* pWhat, Color def) {
		if (!ItemMap[make_pair(pSection, pWhat)].empty()) {
			vector<string> splitVals;
			pUtils.Split(ItemMap[make_pair(pSection, pWhat)], ',', splitVals);

			if (splitVals.size() == 4) {
				return Color(
					atoi(splitVals[0].c_str()),
					atoi(splitVals[1].c_str()),
					atoi(splitVals[2].c_str()),
					atoi(splitVals[3].c_str()));
			}
		}

		return def;
	}

	void SetToggleInt(const char* pSection, const char* pWhat, bool bwhat, int iwhat) {
		char buffer[20];
		_snprintf(buffer, 20, StrEnc("%s,%i"), bwhat ? "true" : "false", iwhat);
		ItemMap[make_pair(pSection, pWhat)] = string(buffer);
	}

	void SetToggleFloat(const char* pSection, const char* pWhat, bool bwhat, float fwhat) {
		char buffer[30];
		_snprintf(buffer, 30, StrEnc("%s,%.f"), bwhat ? "true" : "false", fwhat);
		ItemMap[make_pair(pSection, pWhat)] = string(buffer);
	}

	void SetInt(const char* pSection, const char* pWhat, int val) {
		char buffer[15];
		_snprintf(buffer, 15, StrEnc("%i"), val);
		ItemMap[make_pair(pSection, pWhat)] = string(buffer);
	}

	void SetString(const char* pSection, const char* pWhat, const char* val) {
		ItemMap[make_pair(pSection, pWhat)] = val;
	}

	void SetFloat(const char* pSection, const char* pWhat, float val) {
		char buffer[20];
		_snprintf(buffer, 20, StrEnc("%.3f"), val);
		ItemMap[make_pair(pSection, pWhat)] = string(buffer);
	}

	void SetBool(const char* pSection, const char* pWhat, bool val) {
		char buffer[10];
		_snprintf(buffer, 10, val ? StrEnc("true") : StrEnc("false"));
		ItemMap[make_pair(pSection, pWhat)] = string(buffer);
	}

	void SetColor(const char* pSection, const char* pWhat, Color val) {
		char buffer[17];
		_snprintf(buffer, 17, "%i,%i,%i,%i", val.Color_.R, val.Color_.G, val.Color_.B, val.Color_.A);
		ItemMap[make_pair(pSection, pWhat)] = string(buffer);
	}

	bool IsGood() {
		return bIsGood;
	}

	void SaveToFile(const char* pFileName) {
		FILE* file = fopen(pFileName, StrEnc("w+"));
		if (file) {
			auto sections = GetSections();
			for (int i = 0; i < sections.size(); i++) {
				fprintf(file, StrEnc("[%s]\n"), sections[i].c_str());

				auto data = GetDataFromSection(sections[i].c_str());
				for (int j = 0; j < data.size(); j++) {
					fprintf(file, StrEnc("%s = %s\n"), data[j].first.c_str(), data[j].second.c_str());
				}

				if (i != sections.size() - 1) {
					fprintf(file, StrEnc("\n"));
				}
			}

			fclose(file);
		}
	}

	map<pair<string, string>, string> ItemMap;
private:
	bool bIsGood;

	bool Find(vector<string> mapped, string val) {
		for (int i = 0; i < mapped.size(); i++) {
			if (mapped[i] == val)
				return true;
		}
		return false;
	}
};