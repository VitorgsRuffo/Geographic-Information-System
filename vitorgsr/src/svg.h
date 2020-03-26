#ifndef SVG_H
#define SVG_H

void svg_append_tag_to_final_document(char* *finalTag, char* *svgFinalDocument, char* *svgFinalDocument2);

void svg_finalize_final_document(char* *svgFinalDocument);


void svg_build_circ_tag(char* *tag, char* i, char* rad, char* x, char* y, char* corb, char* corp);

void svg_build_rect_tag(char* *tag, char* i, char* w, char* h, char* x, char* y, char* corb, char* corp);

void svg_build_txt_tag(char* *tag, char* x, char* y, char* corb, char* corp, char* txt);


void svg_interpret_command(char* *command, char* *commandElements, int commandNum);

void svg_draw(char* *command, char* *svgFinalDocument, int commandNum);

void buildSvgPath(Parameter *parameter);

//void buildSvgQryPath(Parameter *parameter);

void svg_qry_o(char* *qryCommand, char* commands[][8], int geo_lines_count);

float svg_rect_point_next_to_circ_center(float min, float max, float value);

#endif