﻿
#include "configxml.h"
#include "corvuscnf.h"
#include "convtable.h"
#include "resource.h"

INT_PTR CALLBACK DlgProcKana(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hWndListView;
	LV_COLUMNW lvc;
	LVITEMW item;
	int index, count;
	ROMAN_KANA_CONV rkc;
	ROMAN_KANA_CONV rkcBak;
	WCHAR soku[8];
	NMLISTVIEW *pListView;

	switch(message)
	{
	case WM_INITDIALOG:
		hWndListView = GetDlgItem(hDlg, IDC_LIST_KANATBL);
		ListView_SetExtendedListViewStyle(hWndListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvc.fmt = LVCFMT_CENTER;

		lvc.iSubItem = 0;
		lvc.cx = 60;
		lvc.pszText = L"ﾛｰﾏ字";
		ListView_InsertColumn(hWndListView, 0, &lvc);
		lvc.iSubItem = 1;
		lvc.cx = 60;
		lvc.pszText = L"かな";
		ListView_InsertColumn(hWndListView, 1, &lvc);
		lvc.iSubItem = 2;
		lvc.cx = 60;
		lvc.pszText = L"カナ";
		ListView_InsertColumn(hWndListView, 2, &lvc);
		lvc.iSubItem = 3;
		lvc.cx = 60;
		lvc.pszText = L"ｶﾅ";
		ListView_InsertColumn(hWndListView, 3, &lvc);
		lvc.iSubItem = 4;
		lvc.cx = 30;
		lvc.pszText = L"…";
		ListView_InsertColumn(hWndListView, 4, &lvc);

		SetDlgItemText(hDlg, IDC_EDIT_KANATBL_R, L"");
		SetDlgItemText(hDlg, IDC_EDIT_KANATBL_H, L"");
		SetDlgItemText(hDlg, IDC_EDIT_KANATBL_K, L"");
		SetDlgItemText(hDlg, IDC_EDIT_KANATBL_KA, L"");
		CheckDlgButton(hDlg, IDC_CHECKBOX_KANATBL_SOKU, BST_UNCHECKED);

		LoadKana(hDlg);

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		hWndListView = GetDlgItem(hDlg, IDC_LIST_KANATBL);
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON_KANATBL_W:
			index = ListView_GetNextItem(hWndListView, -1, LVNI_SELECTED);
			count = ListView_GetItemCount(hWndListView);
			if(index >= 0)
			{
				PropSheet_Changed(GetParent(hDlg), hDlg);

				GetDlgItemText(hDlg, IDC_EDIT_KANATBL_R, rkc.roman, _countof(rkc.roman));
				GetDlgItemText(hDlg, IDC_EDIT_KANATBL_H, rkc.hiragana, _countof(rkc.hiragana));
				GetDlgItemText(hDlg, IDC_EDIT_KANATBL_K, rkc.katakana, _countof(rkc.katakana));
				GetDlgItemText(hDlg, IDC_EDIT_KANATBL_KA, rkc.katakana_ank, _countof(rkc.katakana_ank));
				IsDlgButtonChecked(hDlg, IDC_CHECKBOX_KANATBL_SOKU) == BST_CHECKED ? rkc.soku = TRUE : rkc.soku = FALSE;
				SetDlgItemText(hDlg, IDC_EDIT_KANATBL_R, rkc.roman);
				SetDlgItemText(hDlg, IDC_EDIT_KANATBL_H, rkc.hiragana);
				SetDlgItemText(hDlg, IDC_EDIT_KANATBL_K, rkc.katakana);
				SetDlgItemText(hDlg, IDC_EDIT_KANATBL_KA, rkc.katakana_ank);
				ListView_SetItemText(hWndListView, index, 0, rkc.roman);
				ListView_SetItemText(hWndListView, index, 1, rkc.hiragana);
				ListView_SetItemText(hWndListView, index, 2, rkc.katakana);
				ListView_SetItemText(hWndListView, index, 3, rkc.katakana_ank);
				ListView_SetItemText(hWndListView, index, 4, rkc.soku ? L"1" : L"0");
			}
			else if(count < ROMAN_KANA_TBL_NUM)
			{
				PropSheet_Changed(GetParent(hDlg), hDlg);

				GetDlgItemText(hDlg, IDC_EDIT_KANATBL_R, rkc.roman, _countof(rkc.roman));
				GetDlgItemText(hDlg, IDC_EDIT_KANATBL_H, rkc.hiragana, _countof(rkc.hiragana));
				GetDlgItemText(hDlg, IDC_EDIT_KANATBL_K, rkc.katakana, _countof(rkc.katakana));
				GetDlgItemText(hDlg, IDC_EDIT_KANATBL_KA, rkc.katakana_ank, _countof(rkc.katakana_ank));
				IsDlgButtonChecked(hDlg, IDC_CHECKBOX_KANATBL_SOKU) == BST_CHECKED ? rkc.soku = TRUE : rkc.soku = FALSE;
				SetDlgItemText(hDlg, IDC_EDIT_KANATBL_R, rkc.roman);
				SetDlgItemText(hDlg, IDC_EDIT_KANATBL_H, rkc.hiragana);
				SetDlgItemText(hDlg, IDC_EDIT_KANATBL_K, rkc.katakana);
				SetDlgItemText(hDlg, IDC_EDIT_KANATBL_KA, rkc.katakana_ank);
				item.mask = LVIF_TEXT;
				item.pszText = rkc.roman;
				item.iItem = count;
				item.iSubItem = 0;
				ListView_InsertItem(hWndListView, &item);
				item.pszText = rkc.hiragana;
				item.iItem = count;
				item.iSubItem = 1;
				ListView_SetItem(hWndListView, &item);
				item.pszText = rkc.katakana;
				item.iItem = count;
				item.iSubItem = 2;
				ListView_SetItem(hWndListView, &item);
				item.pszText = rkc.katakana_ank;
				item.iItem = count;
				item.iSubItem = 3;
				ListView_SetItem(hWndListView, &item);
				item.pszText = (rkc.soku == TRUE ? L"1" : L"0");
				item.iItem = count;
				item.iSubItem = 4;
				ListView_SetItem(hWndListView, &item);
			}
			return (INT_PTR)TRUE;

		case IDC_BUTTON_KANATBL_D:
			index = ListView_GetNextItem(hWndListView, -1, LVNI_SELECTED);
			if(index != -1)
			{
				PropSheet_Changed(GetParent(hDlg), hDlg);

				ListView_DeleteItem(hWndListView, index);
			}
			return (INT_PTR)TRUE;

		case IDC_BUTTON_KANATBL_UP:
			index = ListView_GetNextItem(hWndListView, -1, LVNI_SELECTED);
			if(index > 0)
			{
				PropSheet_Changed(GetParent(hDlg), hDlg);

				ListView_GetItemText(hWndListView, index - 1, 0, rkcBak.roman, _countof(rkcBak.roman));
				ListView_GetItemText(hWndListView, index - 1, 1, rkcBak.hiragana, _countof(rkcBak.hiragana));
				ListView_GetItemText(hWndListView, index - 1, 2, rkcBak.katakana, _countof(rkcBak.katakana));
				ListView_GetItemText(hWndListView, index - 1, 3, rkcBak.katakana_ank, _countof(rkcBak.katakana_ank));
				ListView_GetItemText(hWndListView, index - 1, 4, soku, _countof(soku));
				soku[0] == L'1' ? rkcBak.soku = TRUE : rkcBak.soku = FALSE;
				ListView_GetItemText(hWndListView, index, 0, rkc.roman, _countof(rkc.roman));
				ListView_GetItemText(hWndListView, index, 1, rkc.hiragana, _countof(rkc.hiragana));
				ListView_GetItemText(hWndListView, index, 2, rkc.katakana, _countof(rkc.katakana));
				ListView_GetItemText(hWndListView, index, 3, rkc.katakana_ank, _countof(rkc.katakana_ank));
				ListView_GetItemText(hWndListView, index, 4, soku, _countof(soku));
				soku[0] == L'1' ? rkc.soku = TRUE : rkc.soku = FALSE;
				ListView_SetItemText(hWndListView, index - 1, 0, rkc.roman);
				ListView_SetItemText(hWndListView, index - 1, 1, rkc.hiragana);
				ListView_SetItemText(hWndListView, index - 1, 2, rkc.katakana);
				ListView_SetItemText(hWndListView, index - 1, 3, rkc.katakana_ank);
				ListView_SetItemText(hWndListView, index - 1, 4, rkc.soku ? L"1" : L"0");
				ListView_SetItemText(hWndListView, index, 0, rkcBak.roman);
				ListView_SetItemText(hWndListView, index, 1, rkcBak.hiragana);
				ListView_SetItemText(hWndListView, index, 2, rkcBak.katakana);
				ListView_SetItemText(hWndListView, index, 3, rkcBak.katakana_ank);
				ListView_SetItemText(hWndListView, index, 4, rkcBak.soku ? L"1" : L"0");
				ListView_SetItemState(hWndListView, index - 1, LVIS_FOCUSED | LVIS_SELECTED, 0x000F);
			}
			return (INT_PTR)TRUE;

		case IDC_BUTTON_KANATBL_DOWN:
			index = ListView_GetNextItem(hWndListView, -1, LVNI_SELECTED);
			count = ListView_GetItemCount(hWndListView);
			if(index >= 0 && index < count - 1)
			{
				PropSheet_Changed(GetParent(hDlg), hDlg);

				ListView_GetItemText(hWndListView, index + 1, 0, rkcBak.roman, _countof(rkcBak.roman));
				ListView_GetItemText(hWndListView, index + 1, 1, rkcBak.hiragana, _countof(rkcBak.hiragana));
				ListView_GetItemText(hWndListView, index + 1, 2, rkcBak.katakana, _countof(rkcBak.katakana));
				ListView_GetItemText(hWndListView, index + 1, 3, rkcBak.katakana_ank, _countof(rkcBak.katakana_ank));
				ListView_GetItemText(hWndListView, index + 1, 4, soku, _countof(soku));
				soku[0] == L'1' ? rkcBak.soku = TRUE : rkcBak.soku = FALSE;
				ListView_GetItemText(hWndListView, index, 0, rkc.roman, _countof(rkc.roman));
				ListView_GetItemText(hWndListView, index, 1, rkc.hiragana, _countof(rkc.hiragana));
				ListView_GetItemText(hWndListView, index, 2, rkc.katakana, _countof(rkc.katakana));
				ListView_GetItemText(hWndListView, index, 3, rkc.katakana_ank, _countof(rkc.katakana_ank));
				ListView_GetItemText(hWndListView, index, 4, soku, _countof(soku));
				soku[0] == L'1' ? rkc.soku = TRUE : rkc.soku = FALSE;
				ListView_SetItemText(hWndListView, index + 1, 0, rkc.roman);
				ListView_SetItemText(hWndListView, index + 1, 1, rkc.hiragana);
				ListView_SetItemText(hWndListView, index + 1, 2, rkc.katakana);
				ListView_SetItemText(hWndListView, index + 1, 3, rkc.katakana_ank);
				ListView_SetItemText(hWndListView, index + 1, 4, rkc.soku ? L"1" : L"0");
				ListView_SetItemText(hWndListView, index, 0, rkcBak.roman);
				ListView_SetItemText(hWndListView, index, 1, rkcBak.hiragana);
				ListView_SetItemText(hWndListView, index, 2, rkcBak.katakana);
				ListView_SetItemText(hWndListView, index, 3, rkcBak.katakana_ank);
				ListView_SetItemText(hWndListView, index, 4, rkcBak.soku ? L"1" : L"0");
				ListView_SetItemState(hWndListView, index + 1, LVIS_FOCUSED | LVIS_SELECTED, 0x000F);
			}
			return (INT_PTR)TRUE;

		default:
			break;
		}
		break;

	case WM_NOTIFY:
		switch(((LPNMHDR)lParam)->code)
		{
		case LVN_ITEMCHANGED:
			pListView = (NMLISTVIEW*)((LPNMHDR)lParam);
			if(pListView->uChanged & LVIF_STATE)
			{
				hWndListView = ((LPNMHDR)lParam)->hwndFrom;
				index = ListView_GetNextItem(hWndListView, -1, LVNI_SELECTED);
				if(index == -1)
				{
					SetDlgItemText(hDlg, IDC_EDIT_KANATBL_R, L"");
					SetDlgItemText(hDlg, IDC_EDIT_KANATBL_H, L"");
					SetDlgItemText(hDlg, IDC_EDIT_KANATBL_K, L"");
					SetDlgItemText(hDlg, IDC_EDIT_KANATBL_KA, L"");
					CheckDlgButton(hDlg, IDC_CHECKBOX_KANATBL_SOKU, BST_UNCHECKED);
				}
				else
				{
					ListView_GetItemText(hWndListView, index, 0, rkc.roman, _countof(rkc.roman));
					ListView_GetItemText(hWndListView, index, 1, rkc.hiragana, _countof(rkc.roman));
					ListView_GetItemText(hWndListView, index, 2, rkc.katakana, _countof(rkc.roman));
					ListView_GetItemText(hWndListView, index, 3, rkc.katakana_ank, _countof(rkc.roman));
					ListView_GetItemText(hWndListView, index, 4, soku, _countof(soku));
					soku[0] == L'1' ? rkc.soku = TRUE : rkc.soku = FALSE;
					SetDlgItemText(hDlg, IDC_EDIT_KANATBL_R, rkc.roman);
					SetDlgItemText(hDlg, IDC_EDIT_KANATBL_H, rkc.hiragana);
					SetDlgItemText(hDlg, IDC_EDIT_KANATBL_K, rkc.katakana);
					SetDlgItemText(hDlg, IDC_EDIT_KANATBL_KA, rkc.katakana_ank);
					CheckDlgButton(hDlg, IDC_CHECKBOX_KANATBL_SOKU, (rkc.soku == TRUE ? BST_CHECKED : BST_UNCHECKED));
				}
				return (INT_PTR)TRUE;
			}
			break;

		case PSN_APPLY:
			SaveKana(hDlg);
			return (INT_PTR)TRUE;

		default:
			break;
		}
		break;
	}

	return (INT_PTR)FALSE;
}