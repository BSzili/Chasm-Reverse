uniform mat4 view_matrix;
uniform mat3 lightmap_matrix;
uniform int enabled_groups_mask;

in vec3 pos;
in vec2 tex_coord;
in float alpha_test_mask;
in int groups_mask;

out vec2 f_tex_coord;
out vec2 f_lightmap_coord;
out float f_alpha_test_mask; // Polugon neeeds alpha-test
out float f_discard_mask; // Polygon discard

void main()
{
	f_tex_coord= tex_coord;
	f_lightmap_coord= ( lightmap_matrix * vec3( pos.xy, 1.0 ) ).xy;
	f_alpha_test_mask= alpha_test_mask;
	f_discard_mask= ( enabled_groups_mask & groups_mask ) == 0 ? 0.0 : 1.0;
	gl_Position= view_matrix * vec4( pos, 1.0 );
}