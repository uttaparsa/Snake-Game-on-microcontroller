#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <conio.h>
//#include <winuser.h>
#include <windows.h>
#include "rs232.h"
#include <thread> 
#include <fstream>
#define DIR_KEYS "wasdr"
#define GAME_STATE_SIZE 150
#define RECEIVE_BUFFER_SIZE 400

using namespace std;
#include "olcConsoleGameEngine.h"
unsigned char recv_temp_buffer[GAME_STATE_SIZE];
unsigned char receive_store_buffer[RECEIVE_BUFFER_SIZE];
unsigned char pureData[GAME_STATE_SIZE];
ofstream myfile;
char sendFlag = 0;
int FPS = 10;
class Snake : public olcConsoleGameEngine
{
public:
	int com_index;
	Snake(int index) {
		m_sAppName = L"Snake Game";
		com_index = index;
	}
private:
	string sLevel;
	int nLevelWidth;
	int nLevelHeight;
	int stringLookupLevel;
	float prevFrameElapsed;
	int frameNumber;
	char send_buffer[2];
	std::ofstream saveFile;
	int snakeScore;

protected:
	virtual bool OnUserCreate() {
		nLevelWidth = 20;
		nLevelHeight = 8;
		emptyLevel();
		prevFrameElapsed = 0;
		frameNumber = 0;
		receive_store_buffer[0] = '\0';
		send_buffer[1] = '\0';
		myfile.open("mylog.txt");
		snakeScore = 0;
		return true;
	}

	virtual bool purifyReceiveBuffer() {
		// É = ascii 201
		char* start;
		char* end;
		start = strchr((char*)receive_store_buffer,'É');
		end = strchr((char*)receive_store_buffer, 'É'+1);
		
		if (start && end) {
			int messageStartIndex = (int)(start - (char*)receive_store_buffer) + 1;
			int messageEndIndex = (int)(end - (char*)receive_store_buffer);
			myfile << "start = " << messageStartIndex << " end = " << messageEndIndex << std::endl;
			int pureDataSize = messageEndIndex - messageStartIndex;
			if (pureDataSize > 0) {
				memset(pureData, 0, strlen((char*)pureData));
				memcpy(pureData, &receive_store_buffer[messageStartIndex], pureDataSize);
				memset(receive_store_buffer, 0, strlen((char*)receive_store_buffer));
				pureData[pureDataSize] = '\0';
				return true;
			}
			else if (start) {
				memset(receive_store_buffer, 0, messageStartIndex - 1);
			}

		}


		return false;
	}
	
	virtual void concatTempToReceiveBuffer() {
		 strcat((char*)receive_store_buffer, (char*) recv_temp_buffer);
	}
	virtual void emptyLevel() {
		sLevel = "....................";
		sLevel += "....................";
		sLevel += "....................";
		sLevel += "....................";
		sLevel += "....................";
		sLevel += "....................";
		sLevel += "....................";
		sLevel += "....................";
	}
	virtual bool OnUserUpdate(float fElapsedTime) {
		prevFrameElapsed += fElapsedTime;


		if (prevFrameElapsed > (float)1 / (float)FPS) {
			

			// Utility lambda
			auto GetTile = [&](int x, int y)
			{
				if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
					return sLevel[y * nLevelWidth + x];
				else
					return ' ';
			};

			auto SetTile = [&](int x, int y, wchar_t c)
			{
				if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
					sLevel[y * nLevelWidth + x] = c;
			};

			int nTileWidth = 4;
			int nTileHeight = 4;
			int nVisibleTilesX = ScreenWidth() / nTileWidth;
			int nVisibleTilesY = ScreenHeight() / nTileHeight;



			// Handle Input

			memset(recv_temp_buffer, 0, GAME_STATE_SIZE);
			comRead(com_index, (char*)recv_temp_buffer, GAME_STATE_SIZE);
			myfile << "\nFrame number " << ++frameNumber << endl;
			myfile << "temp buffer : ";
			for (int i = 0; i < strlen((char*)recv_temp_buffer); ++i) {
				myfile << (int)recv_temp_buffer[i] << ", ";
			}
			myfile << " length=" << strlen((char*)recv_temp_buffer);
			myfile << endl;
			concatTempToReceiveBuffer();
			if (purifyReceiveBuffer()) {
				myfile << "PURE BUFFER : ";
				for (int i = 0; i < strlen((char*) pureData) ; ++i) {
					myfile << (int)pureData[i] << ", ";
				}
				myfile << endl;
				emptyLevel();
				stringLookupLevel = 0;

				for (int i = 0; i < strlen((char*)pureData); ++i) {
					if ((int)pureData[i] < 170) {
						if (stringLookupLevel == 0) {
							sLevel[(int)pureData[i]-1] = '#';
						}
						else if (stringLookupLevel == 1) {
							sLevel[(int)pureData[i]-1] = 'A';
						}
						else if (stringLookupLevel == 4) {
							snakeScore = ((int)pureData[i] - 1)*10;
						}
					}
					else {
						stringLookupLevel += 1;
					}
				}
			}
			else {
				myfile << "NOT PURE : ";
				for (int i = 0; i < strlen((char*)receive_store_buffer) ; ++i) {
					myfile << (int)receive_store_buffer[i] << ", ";
				}
				myfile << endl;
			}
			if (sendFlag) {
				comWrite(com_index, send_buffer, 1);
				sendFlag = false;
				myfile << send_buffer[0] << " sent..." << endl;
			}
			

			// Draw Level
			for (int x = 0; x < nVisibleTilesX; ++x) {
				for (int y = 0; y < nVisibleTilesY; ++y) {
					char sTileID = GetTile(x, y);
					switch (sTileID)
					{
					case '.':
						Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_CYAN);
						break;
					case '#':
						Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_GREEN);
						break;
					case 'A':
						Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_RED);
						break;
					default:
						break;
					}
				}
			}

			DrawString(0, 0, L"Score: " + to_wstring(snakeScore));
			prevFrameElapsed = 0;
		}
		if (IsFocused())
		{
			string keys = "WASDR";
			for (int i = 0; i < keys.length(); ++i) {
				if (GetKey(keys[i]).bHeld)
				{
					send_buffer[0] = keys[i]+32;
					sendFlag = true;
				}

			}
			if (GetKey('F').bPressed) {
				myfile << "F pressed" << std::endl;
				saveFile.open("save.txt");
				for (int i = 0; i < strlen((char*) pureData); ++i) {
					saveFile << (int)pureData[i] << " ";
				}
				saveFile << std::endl;
				saveFile.close();
			}
			if (GetKey('L').bPressed) {
				myfile << "L pressed" << std::endl;
				std::fstream loadFile("save.txt", std::ios_base::in);
				//start message
				send_buffer[0] = 201;
				comWrite(com_index, send_buffer, 1);


				int data;
				while (loadFile >> data)
				{
					send_buffer[0] = data;
					comWrite(com_index, send_buffer, 1);
				}

				//end message
				send_buffer[0] = 202;
				comWrite(com_index, send_buffer, 1);
			}

		}
		return true;
	}
	virtual bool  OnUserDestroy() {

		myfile.close();

		return true;
	}
};

int main() {

	printf("%d\n", comEnumerate());
	int com_index = comFindPort("COM7");
	printf("%s\n", comGetPortName(com_index));
	comOpen(com_index, 9600);
	Snake game(com_index);



	if (game.ConstructConsole(80, 32, 8, 8)) {
		game.Start();
	}
	comClose(com_index);
	comTerminate();

	return 0;

}