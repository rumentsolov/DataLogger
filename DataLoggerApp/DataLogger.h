#pragma once

#include "trend.h"

namespace DataLoggerApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DataLogger
	/// </summary>
	public ref class DataLogger : public System::Windows::Forms::Form
	{
	public:
		DataLogger(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~DataLogger()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btn1;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
		

			this->btn1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btn1
			// 
			this->btn1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn1->Location = System::Drawing::Point(41, 54);
			this->btn1->Name = L"btn1";
			this->btn1->Size = System::Drawing::Size(182, 108);
			this->btn1->TabIndex = 0;
			this->btn1->Text = L"GO";
			this->btn1->UseVisualStyleBackColor = true;
			this->btn1->Click += gcnew System::EventHandler(this, &DataLogger::btn1_Click);
			// 
			// DataLogger
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->btn1);
			this->Name = L"DataLogger";
			this->Text = L"DataLogger";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btn1_Click(System::Object^ sender, System::EventArgs^ e) {

		run();

	}
	};
}
