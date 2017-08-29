/*************************************************************************/
/*  navigation_polygon_editor_plugin.h                                   */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2017 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2017 Godot Engine contributors (cf. AUTHORS.md)    */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#ifndef NAVIGATIONPOLYGONEDITORPLUGIN_H
#define NAVIGATIONPOLYGONEDITORPLUGIN_H

#include "editor/plugins/abstract_polygon_2d_editor.h"
#include "scene/2d/navigation_polygon.h"

/**
	@author Juan Linietsky <reduzio@gmail.com>
*/
class NavigationPolygonEditor : public AbstractPolygon2DEditor {

	GDCLASS(NavigationPolygonEditor, AbstractPolygon2DEditor);

	enum Mode {

		MODE_CREATE,
		MODE_EDIT,

	};

	Mode mode;

	ToolButton *button_create;
	ToolButton *button_edit;

	ConfirmationDialog *create_nav;

	NavigationPolygonInstance *node;

	void _create_nav();

	void _menu_option(int p_option);

protected:
	virtual void _enter_edit_mode();
	virtual bool _is_in_create_mode() const;
	virtual bool _is_in_edit_mode() const;

	virtual Node2D *_get_node() const;
	virtual void _set_node(Node *p_node);

	virtual int _get_polygon_count() const;
	virtual Vector<Vector2> _get_polygon(int p_polygon) const;
	virtual void _set_polygon(int p_polygon, const Vector<Vector2> &p_points) const;
	virtual Vector2 _get_offset() const;

	virtual bool _is_wip_destructive() const;
	virtual void _create_wip_close_action(const Vector<Vector2> &p_wip);
	virtual void _create_edit_poly_action(int p_polygon, const Vector<Vector2> &p_before, const Vector<Vector2> &p_after);
	virtual void _create_remove_point_action(int p_polygon, int p_point);

	virtual Color _get_previous_outline_color() const;

	virtual bool _can_input(const Ref<InputEvent> &p_event, bool &p_ret) const;
	virtual bool _can_draw() const;

	void _notification(int p_what);
	static void _bind_methods();

public:
	NavigationPolygonEditor(EditorNode *p_editor);
};

class NavigationPolygonEditorPlugin : public EditorPlugin {

	GDCLASS(NavigationPolygonEditorPlugin, EditorPlugin);

	NavigationPolygonEditor *collision_polygon_editor;
	EditorNode *editor;

public:
	virtual bool forward_canvas_gui_input(const Transform2D &p_canvas_xform, const Ref<InputEvent> &p_event) { return collision_polygon_editor->forward_gui_input(p_event); }

	virtual String get_name() const { return "NavigationPolygonInstance"; }
	bool has_main_screen() const { return false; }
	virtual void edit(Object *p_object);
	virtual bool handles(Object *p_object) const;
	virtual void make_visible(bool p_visible);

	NavigationPolygonEditorPlugin(EditorNode *p_node);
	~NavigationPolygonEditorPlugin();
};

#endif // NAVIGATIONPOLYGONEDITORPLUGIN_H
