#pragma once
#include<iscsierr.h>
#include <iscsidsc.h>

namespace NASmonitor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		bool connected = "Not connected";
	private: System::Windows::Forms::Label^ Counter;
	private: System::Windows::Forms::Label^ RefreshTitle;

	private: System::Windows::Forms::Label^ statusTitle;
	private: System::Windows::Forms::Label^ PortTitle;
	private: System::Windows::Forms::Label^ IPTitle;
	private: System::Windows::Forms::Label^ Status1;
	private: System::Windows::Forms::Label^ IP1;
	private: System::Windows::Forms::Label^ port1;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	public:
		int RefreshCounter = 0;

		MyForm(void)
		{
			connected = InitLink();
			InitializeComponent();

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}


	protected:

	private:

		//change these to suit your iSCSI server needs
		const char* IP = "192.168.0.250";
		const int unsigned short PORT = 3260;

	private: System::Windows::Forms::Timer^ timer1;

		   bool InitLink()
		   {
			   ISDSC_STATUS Status = NULL;

			   ULONG Buffer = (ULONG)4000UL;
			   ULONG* BufferSize = &Buffer;

			   ULONG SessionCount = (ULONG)2UL;
			   ULONG* pSessionCount = &SessionCount;

			   PISCSI_SESSION_INFOA pSessionInfo = new ISCSI_SESSION_INFOA[20];
			   try
			   {
				   Status = GetIScsiSessionListA(BufferSize, pSessionCount, pSessionInfo);
			   }
			   catch (int x)
			   {
				   std::cout << "\n" << "Exception: " << x;
			   }

			   //If it fails due to small buffer, this retries with a larger buffer.
			   //BufferSize returns the correct size
			   if (Status == ERROR_INSUFFICIENT_BUFFER)
			   {
				   Status = GetIScsiSessionListA(BufferSize, pSessionCount, pSessionInfo);
			   }

			   if (Status != 0)
			   {
				   return false;
			   }


			   ULONG ConnectionCount = pSessionInfo->ConnectionCount;

			   if (ConnectionCount == 0)
			   {
				   delete[] pSessionInfo;
				   return false;
			   }

			   PCHAR TargetAddress = pSessionInfo->Connections->TargetAddress;
			   USHORT TargetSocket = pSessionInfo->Connections->TargetSocket;

			   if (*TargetAddress == *IP && TargetSocket == PORT)
			   {
				   delete[] pSessionInfo;
				   return true;
			   }
			   else
			   {
				   delete[] pSessionInfo;
				   return false;
			   }

		   }
private: System::ComponentModel::IContainer^ components;

		   /// <summary>
		   /// Required designer variable.
		   /// </summary>


#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->Counter = (gcnew System::Windows::Forms::Label());
			   this->RefreshTitle = (gcnew System::Windows::Forms::Label());
			   this->statusTitle = (gcnew System::Windows::Forms::Label());
			   this->PortTitle = (gcnew System::Windows::Forms::Label());
			   this->IPTitle = (gcnew System::Windows::Forms::Label());
			   this->Status1 = (gcnew System::Windows::Forms::Label());
			   this->IP1 = (gcnew System::Windows::Forms::Label());
			   this->port1 = (gcnew System::Windows::Forms::Label());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			   this->panel1->SuspendLayout();
			   this->tableLayoutPanel2->SuspendLayout();
			   this->tableLayoutPanel3->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // timer1
			   // 
			   this->timer1->Enabled = true;
			   this->timer1->Interval = 10000;
			   this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			   // 
			   // Counter
			   // 
			   this->Counter->AutoSize = true;
			   this->Counter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			   this->Counter->Location = System::Drawing::Point(507, 148);
			   this->Counter->Name = L"Counter";
			   this->Counter->Size = System::Drawing::Size(16, 17);
			   this->Counter->TabIndex = 5;
			   this->Counter->Text = L"0";
			   // 
			   // RefreshTitle
			   // 
			   this->RefreshTitle->AutoSize = true;
			   this->RefreshTitle->Location = System::Drawing::Point(414, 150);
			   this->RefreshTitle->Name = L"RefreshTitle";
			   this->RefreshTitle->Size = System::Drawing::Size(87, 13);
			   this->RefreshTitle->TabIndex = 6;
			   this->RefreshTitle->Text = L"Refresh Counter:";
			   // 
			   // statusTitle
			   // 
			   this->statusTitle->AutoSize = true;
			   this->statusTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->statusTitle->Location = System::Drawing::Point(296, 0);
			   this->statusTitle->Name = L"statusTitle";
			   this->statusTitle->Size = System::Drawing::Size(66, 24);
			   this->statusTitle->TabIndex = 1;
			   this->statusTitle->Text = L"Status";
			   // 
			   // PortTitle
			   // 
			   this->PortTitle->AutoSize = true;
			   this->PortTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->PortTitle->Location = System::Drawing::Point(143, 0);
			   this->PortTitle->Name = L"PortTitle";
			   this->PortTitle->Size = System::Drawing::Size(47, 24);
			   this->PortTitle->TabIndex = 3;
			   this->PortTitle->Text = L"Port";
			   // 
			   // IPTitle
			   // 
			   this->IPTitle->AutoSize = true;
			   this->IPTitle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->IPTitle->Location = System::Drawing::Point(3, 0);
			   this->IPTitle->Name = L"IPTitle";
			   this->IPTitle->Size = System::Drawing::Size(28, 24);
			   this->IPTitle->TabIndex = 0;
			   this->IPTitle->Text = L"IP";
			   // 
			   // Status1
			   // 
			   this->Status1->AutoSize = true;
			   this->Status1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->Status1->ForeColor = System::Drawing::Color::Red;
			   this->Status1->Location = System::Drawing::Point(296, 0);
			   this->Status1->Name = L"Status1";
			   this->Status1->Size = System::Drawing::Size(24, 24);
			   this->Status1->TabIndex = 1;
			   this->Status1->Text = L"N";
			   // 
			   // IP1
			   // 
			   this->IP1->AutoSize = true;
			   this->IP1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->IP1->Location = System::Drawing::Point(3, 0);
			   this->IP1->Name = L"IP1";
			   this->IP1->Size = System::Drawing::Size(110, 24);
			   this->IP1->TabIndex = 2;
			   this->IP1->Text = L"192.888.888";
			   // 
			   // port1
			   // 
			   this->port1->AutoSize = true;
			   this->port1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->port1->Location = System::Drawing::Point(143, 0);
			   this->port1->Name = L"port1";
			   this->port1->Size = System::Drawing::Size(30, 24);
			   this->port1->TabIndex = 4;
			   this->port1->Text = L"32";
			   // 
			   // panel1
			   // 
			   this->panel1->BackColor = System::Drawing::Color::MediumSlateBlue;
			   this->panel1->Controls->Add(this->tableLayoutPanel3);
			   this->panel1->Location = System::Drawing::Point(1, 1);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(537, 32);
			   this->panel1->TabIndex = 8;
			   // 
			   // tableLayoutPanel2
			   // 
			   this->tableLayoutPanel2->BackColor = System::Drawing::Color::Transparent;
			   this->tableLayoutPanel2->ColumnCount = 3;
			   this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   47.78157F)));
			   this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   52.21843F)));
			   this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   176)));
			   this->tableLayoutPanel2->Controls->Add(this->port1, 1, 0);
			   this->tableLayoutPanel2->Controls->Add(this->Status1, 2, 0);
			   this->tableLayoutPanel2->Controls->Add(this->IP1, 0, 0);
			   this->tableLayoutPanel2->ForeColor = System::Drawing::Color::Black;
			   this->tableLayoutPanel2->Location = System::Drawing::Point(12, 39);
			   this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			   this->tableLayoutPanel2->RowCount = 1;
			   this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			   this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			   this->tableLayoutPanel2->Size = System::Drawing::Size(470, 43);
			   this->tableLayoutPanel2->TabIndex = 8;
			   // 
			   // tableLayoutPanel3
			   // 
			   this->tableLayoutPanel3->BackColor = System::Drawing::Color::Transparent;
			   this->tableLayoutPanel3->ColumnCount = 3;
			   this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   47.78157F)));
			   this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				   52.21843F)));
			   this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				   176)));
			   this->tableLayoutPanel3->Controls->Add(this->statusTitle, 2, 0);
			   this->tableLayoutPanel3->Controls->Add(this->IPTitle, 0, 0);
			   this->tableLayoutPanel3->Controls->Add(this->PortTitle, 1, 0);
			   this->tableLayoutPanel3->ForeColor = System::Drawing::Color::Black;
			   this->tableLayoutPanel3->Location = System::Drawing::Point(11, 3);
			   this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			   this->tableLayoutPanel3->RowCount = 1;
			   this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			   this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
			   this->tableLayoutPanel3->Size = System::Drawing::Size(470, 43);
			   this->tableLayoutPanel3->TabIndex = 9;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::Color::DimGray;
			   this->ClientSize = System::Drawing::Size(535, 174);
			   this->Controls->Add(this->tableLayoutPanel2);
			   this->Controls->Add(this->panel1);
			   this->Controls->Add(this->RefreshTitle);
			   this->Controls->Add(this->Counter);
			   this->Name = L"MyForm";
			   this->Text = L"MyForm";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   this->panel1->ResumeLayout(false);
			   this->tableLayoutPanel2->ResumeLayout(false);
			   this->tableLayoutPanel2->PerformLayout();
			   this->tableLayoutPanel3->ResumeLayout(false);
			   this->tableLayoutPanel3->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion



	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e)
	{
		IP1->Text = gcnew System::String(IP);
		port1->Text = gcnew System::String(PORT.ToString());
		if (connected)
		{
			Status1->Text = "Connected";
			Status1->ForeColor = System::Drawing::Color::LimeGreen;

		}
		else
		{
			Status1->Text = "Not Connected";
			Status1->ForeColor = System::Drawing::Color::Red;
		}

		Refresh();

	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		RefreshCounter += 1;
		Counter->Text = gcnew System::String(RefreshCounter.ToString());

		connected = InitLink();
		if (connected)
		{
			Status1->Text = "Connected";
			Status1->ForeColor = System::Drawing::Color::LimeGreen;
		}
		else
		{
			Status1->Text = "Not Connected";
			Status1->ForeColor = System::Drawing::Color::Red;
		}

		Refresh();

	}
};
}
