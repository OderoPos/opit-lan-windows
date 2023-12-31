#pragma once

#include <string>
#include "main/ClientThread.h"
#include "main/OpitResultListener.h"

BOOL WINAPI ExitHandlerRoutine(DWORD eventCode);
void sale();
void doVoid();
void reprintLast();
void reprintReceiptById();
void detailedX();
void simpleX();
void lastSettlementCopy();
void startSettlement();
void resolveChooser(int option);

#define UNIQUE_ID "73qyedhyecgyd7efyuaehudsjh"

OpitResultListener resultListener;
ClientThread thread(resultListener);

int __cdecl main(int argc, char** argv) {
	SetConsoleCtrlHandler(ExitHandlerRoutine, TRUE);
	int option;

    do {
		if (!thread.getIsConnected()) {
			while (!thread.start()) {
				std::cout << "client ping" << std::endl;
				Sleep(ONE_SECOND);
			}
		}
		else {
			std::cout << "\nInsert number:" << std::endl;
			std::cout << "1 for Sale" << std::endl;
			std::cout << "2 for Void" << std::endl;
			std::cout << "3 for Reprint Last" << std::endl;
			std::cout << "4 for Reprint Receipt No." << std::endl;
			std::cout << "5 for Detailed X Report" << std::endl;
			std::cout << "6 for Simple X Report" << std::endl;
			std::cout << "7 for Last Settlement Copy" << std::endl;
			std::cout << "8 for Start Settlement" << std::endl;
			std::cout << "9 to Exit" << std::endl;
			std::cout << "Choose option: ";

			std::cin >> option;

			resolveChooser(option);
		}

		Sleep(ONE_SECOND);
    } while (true);

	return 0;
}


void resolveChooser(int option) {
	switch (option) {
		case 1: {
			sale();
			break;
		}
		case 2: {
			doVoid();
			break;
		}
		case 3: {
			reprintLast();
			break;
		}
		case 4: {
			reprintReceiptById();
			break;
		}
		case 5: {
			detailedX();
			break;
		}
		case 6: {
			simpleX();
			break;
		}
		case 7: {
			lastSettlementCopy();
			break;
		}
		case 8: {
			startSettlement();
			break;
		}
		case 9: {
			thread.destroy();
			ExitProcess(0);
			break;
		}
		default: {
			std::cout << "Unknown choice" << std::endl;
			break;
		}
	}
}


void sale() {
	std::cout << "Insert amount: ";
	double amount;
	std::cin >> amount;
	thread.sendPaymentRequest(amount, "RON", UNIQUE_ID);
}


void doVoid() {
	std::cout << "Insert receipt number: ";
	std::string receiptNo;
	std::cin >> receiptNo;
	thread.voidReceipt(receiptNo.c_str(), UNIQUE_ID);
}


void reprintLast() {
	thread.reprintLastReceipt(UNIQUE_ID);
}


void reprintReceiptById() {
	std::cout << "Insert receipt number: ";
	std::string receiptNo;
	std::cin >> receiptNo;
	thread.reprintReceiptNo(receiptNo.c_str(), UNIQUE_ID);
}


void detailedX() {
	thread.getDetailedXReport("RON", UNIQUE_ID);
}


void simpleX() {
	thread.getSimpleXReport("RON", UNIQUE_ID);
}


void lastSettlementCopy() {
	thread.printLastSettlement("RON", UNIQUE_ID);
}


void startSettlement() {
	thread.printSettlement(UNIQUE_ID);
}


BOOL WINAPI ExitHandlerRoutine(DWORD eventCode) {
	/*
	switch (eventCode) {
		case CTRL_CLOSE_EVENT:
			thread.destroy();
			return TRUE;
		}
	*/

	thread.destroy();
	return TRUE;
}