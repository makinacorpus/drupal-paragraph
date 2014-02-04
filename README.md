# Paragraph

Very simple paragraph field type for Drupal 7.

## Usage

Just activate the module and set some fields of this type.

## Configuration

Configuration can only be done at the instance level (field level does not
really brings any value added).

 *  Allow accordion: simple boolean value the user will be able to set to true
    or false for each value. This preset will be ignored in the default
    formatter implementation but allows you to read this variable into the
    field value template and use this boolean pretty much as you wish.

 *  Require title: title may or may not be required for input. Notice that
    changing the setting on an existing field will not alter already existing
    value.

## Theming

There is a *paragraph.tpl.php* template which represent a single paragraph
value: do whatever you need to do with it. There is a few template suggestions
available for you:

 *  paragraph--field_name

 *  paragraph--entity_type--field_name

 *  paragraph--entity_type--bundle

 *  paragraph--entity_type--bundle--field_name

Beware collisions are possible between field name and bundle.
