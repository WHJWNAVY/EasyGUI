#include "demo.h"

/* Define list of all buttons on main screen */
typedef struct {
    gui_id_t id;
    const uint8_t* label;
    gui_id_t win_id;
    win_data_t data;
} main_win_btn_t;

#define BTN_ENTRY(vid, vlabel, vwin_id, create_fn)            { .id = vid, .label = vlabel, .win_id = vwin_id, .data = { .feature_create_fn = create_fn } },

/* Create list of all buttons */
static main_win_btn_t
btns[] = {
    BTN_ENTRY(ID_BTN_MAINWIN_WINDOW, _GT("Window"), ID_WIN_WINDOW, demo_create_feature_window)
    BTN_ENTRY(ID_BTN_MAINWIN_BUTTONS, _GT("Buttons"), ID_WIN_BUTTONS, demo_create_feature_button)
    BTN_ENTRY(ID_BTN_MAINWIN_EDITTEXT, _GT("Edit text"), ID_WIN_EDITTEXT, demo_create_feature_edit_text)
    BTN_ENTRY(ID_BTN_MAINWIN_GRAPH, _GT("Graph"), ID_WIN_GRAPH, demo_create_feature_graph)
    BTN_ENTRY(ID_BTN_MAINWIN_PROGBAR, _GT("Progress bar"), ID_WIN_PROGBAR, demo_create_feature_progbar)
    BTN_ENTRY(ID_BTN_MAINWIN_LED, _GT("Led"), ID_WIN_LED, demo_create_feature_led)
    BTN_ENTRY(ID_BTN_MAINWIN_LIST_CONTAINER, _GT("ListContainer"), ID_WIN_LIST_CONTAINER, demo_create_feature_list_container)
    BTN_ENTRY(ID_BTN_MAINWIN_TEXTVIEW, _GT("Text view"), ID_WIN_TEXTVIEW, demo_create_feature_text_view)
    BTN_ENTRY(ID_BTN_MAINWIN_SLIDER, _GT("Slider"), ID_WIN_SLIDER, demo_create_feature_slider)
    BTN_ENTRY(ID_BTN_MAINWIN_LISTBOX, _GT("Listbox"), ID_WIN_LISTBOX, demo_create_feature_listbox)
    BTN_ENTRY(ID_BTN_MAINWIN_LISTVIEW, _GT("Listview"), ID_WIN_LISTVIEW, demo_create_feature_listview)
    BTN_ENTRY(ID_BTN_MAINWIN_DROPDOWN, _GT("Dropdown"), ID_WIN_DROPDOWN, demo_create_feature_dropdown)
    BTN_ENTRY(ID_BTN_MAINWIN_CHECKBOX, _GT("Checkbox"), ID_WIN_CHECKBOX, demo_create_feature_checkbox)
    BTN_ENTRY(ID_BTN_MAINWIN_RADIO, _GT("Radiobox"), ID_WIN_RADIO, demo_create_feature_radio)
};

static uint8_t  main_win_btn_callback(gui_handle_p h, gui_wc_t wc, gui_widget_param_t* param, gui_widget_result_t* result);

/**
 * \brief           Initialize demonstration
 */
void
demo_init(void) {
    size_t i;
    gui_handle_p h, parent;
                                                
    gui_protect(1);
    
    gui_widget_setfontdefault(&GUI_Font_Arial_Bold_18);     /* Set default font */
    gui_keyboard_create();
    
    parent = gui_window_getdesktop();           /* Get desktop widget */

    /* Create list container on left side for all buttons */
    parent = gui_listcontainer_create(0, 0, 0, 10, 10, parent, NULL, GUI_FLAG_WIDGET_CREATE_IGNORE_INVALIDATE);
    gui_widget_setpositionpercent(parent, 1, 1);
    gui_widget_setsizepercent(parent, 28, 98);
    gui_listcontainer_setcolor(parent, GUI_LISTCONTAINER_COLOR_BG, GUI_COLOR_DARKGRAY);
    gui_listcontainer_setmode(parent, GUI_LISTCONTAINER_MODE_VERTICAL);
    gui_widget_setpadding(parent, 5);
    gui_widget_setignoreinvalidate(parent, 0, 1);

    /* Print all buttons on container */
    for (i = 0; i < GUI_COUNT_OF(btns); i++) {
        h = gui_button_create(btns[i].id,
            0, 0, 0, 0,
            parent, main_win_btn_callback, GUI_FLAG_WIDGET_CREATE_IGNORE_INVALIDATE
        );
        gui_widget_setpositionpercent(h, 0, GUI_FLOAT(i * 10));
        gui_widget_setsizepercent(h, 100, 8.5f);
        gui_widget_settext(h, _GT(btns[i].label));
        btns[i].data.id = btns[i].win_id;
        btns[i].data.title = btns[i].label;
        gui_widget_setuserdata(h, (void *)&btns[i].data);
        gui_widget_setignoreinvalidate(h, 0, 1);
    }

    gui_unprotect(1);
}

/**
 * \brief           Callback function for main window buttons
 */
static uint8_t
main_win_btn_callback(gui_handle_p h, gui_wc_t wc, gui_widget_param_t* param, gui_widget_result_t* result) {
    uint8_t ret = gui_widget_processdefaultcallback(h, wc, param, result);
    switch (wc) {
        case GUI_WC_Click: {
            demo_create_feature(gui_widget_getuserdata(h), 0);      /* Create feature */
            break;
        }
        default: break;
    }
    return ret;
}
