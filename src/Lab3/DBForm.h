#pragma once

#include <fstream>
#include "../Lab3_code/validation_functions.h"
#include <msclr\marshal_cppstd.h>

namespace Lab3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	/// <summary>
	/// Summary for DBForm
	/// </summary>
	public ref class DBForm : public System::Windows::Forms::Form
	{
	public:
		DBForm(void)
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
		~DBForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ DB_creation_btn;
	private: System::Windows::Forms::Button^ DB_opening_btn;
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
			this->DB_creation_btn = (gcnew System::Windows::Forms::Button());
			this->DB_opening_btn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// DB_creation_btn
			// 
			this->DB_creation_btn->Location = System::Drawing::Point(67, 38);
			this->DB_creation_btn->Name = L"DB_creation_btn";
			this->DB_creation_btn->Size = System::Drawing::Size(148, 75);
			this->DB_creation_btn->TabIndex = 0;
			this->DB_creation_btn->Text = L"Create new DB";
			this->DB_creation_btn->UseVisualStyleBackColor = true;
			this->DB_creation_btn->Click += gcnew System::EventHandler(this, &DBForm::DB_creation_btn_Click);
			// 
			// DB_opening_btn
			// 
			this->DB_opening_btn->Location = System::Drawing::Point(67, 148);
			this->DB_opening_btn->Name = L"DB_opening_btn";
			this->DB_opening_btn->Size = System::Drawing::Size(148, 75);
			this->DB_opening_btn->TabIndex = 1;
			this->DB_opening_btn->Text = L"Open existing DB";
			this->DB_opening_btn->UseVisualStyleBackColor = true;
			this->DB_opening_btn->Click += gcnew System::EventHandler(this, &DBForm::DB_opening_btn_Click);
			// 
			// DBForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(286, 285);
			this->Controls->Add(this->DB_opening_btn);
			this->Controls->Add(this->DB_creation_btn);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"DBForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"BTree Database";
			this->Load += gcnew System::EventHandler(this, &DBForm::DBForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void DBForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: Void DB_creation_btn_Click(Object^ sender, EventArgs^ e);
	private: System::Void DB_opening_btn_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
