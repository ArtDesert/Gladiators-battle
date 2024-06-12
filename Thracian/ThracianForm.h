#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <vector>
#include <thread>
#include <time.h>
#include <string>
#include <mutex>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <winsock2.h>
namespace Thracian {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	WSAData wsaData;
	WORD Dllversion = MAKEWORD(2, 1);
	SOCKADDR_IN addr;
	int sizeofAddr = sizeof(addr);
	SOCKET connection;

	/// <summary>
	/// ������ ��� ThracianForm
	/// </summary>
	public ref class ThracianForm : public System::Windows::Forms::Form
	{
	public:
		ThracianForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~ThracianForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Label^ label1;
	protected:

	private:
		/// <summary>
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Info;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->richTextBox1->Enabled = false;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(12, 49);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(460, 150);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &ThracianForm::richTextBox1_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::Teal;
			this->label1->Location = System::Drawing::Point(44, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(402, 24);
			this->label1->TabIndex = 6;
			this->label1->Text = L"����� ���������� �� ������������� ����!";
			// 
			// ThracianForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(484, 211);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->richTextBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"ThracianForm";
			this->Text = L"�������";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ThracianForm::ThracianForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &ThracianForm::ThracianForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void ThracianForm_Load(System::Object^ sender, System::EventArgs^ e) {
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;
		if (WSAStartup(Dllversion, &wsaData))
		{
		}
		connection = socket(AF_INET, SOCK_STREAM, NULL);
		if (connect(connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
		{
		}
		char c;
		recv(connection, &c, sizeof(c), NULL);
		String^ str = "�� ������������ � ������������� �����!\n��� �����: " + (char)(c - 48) + ", ��� ���: �������\n";
		richTextBox1->Text = str;
	}
	private: System::Void ThracianForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		/*
		System::Windows::Forms::DialogResult dialog = MessageBox::Show(
			"�� ������������� ������ ����� �� ���������?",
			"���������� ���������",
			MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		if (dialog == System::Windows::Forms::DialogResult::Yes) {
			e->Cancel = false;
			closesocket(connection);
			WSACleanup(); //�������������� ���������� Winsock
			Environment::Exit(0);
		}
		else e->Cancel = true;
		*/
		e->Cancel = false;
		closesocket(connection);
		WSACleanup(); //�������������� ���������� Winsock
		Environment::Exit(0);
	}
	};
}
