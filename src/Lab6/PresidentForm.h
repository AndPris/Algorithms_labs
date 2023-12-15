#pragma once

#include "PresidentI.h"

namespace Lab6 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PresidentForm
	/// </summary>
	public ref class PresidentForm : public System::Windows::Forms::Form
	{
	private:
		PresidentI* president;
	public:
		PresidentForm(void);

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PresidentForm();

	private: System::Windows::Forms::FlowLayoutPanel^ humanCards;
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
			this->humanCards = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->SuspendLayout();
			// 
			// humanCards
			// 
			this->humanCards->Location = System::Drawing::Point(148, 797);
			this->humanCards->Name = L"humanCards";
			this->humanCards->Size = System::Drawing::Size(1608, 261);
			this->humanCards->TabIndex = 0;
			// 
			// PresidentForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::OliveDrab;
			this->ClientSize = System::Drawing::Size(1924, 1055);
			this->Controls->Add(this->humanCards);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"PresidentForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"President";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
