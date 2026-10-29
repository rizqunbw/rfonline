vs.1.1
;------------------------------------------------------------------------------
; c0-c3 매트릭스 1 
; c4-c7 매트릭스 2
; c8	포그
; c9  x=흔들수치 ,y=알파
; c12- 버텍스 쉐이더의 상황에 따른 셋팅.
;
; Vertex components 
;    v0    = Position
;------------------------------------------------------------------------------

dcl_position0	v0
dcl_color	v3
dcl_texcoord0	v4
;------------------------------------------------------------------------------
; Vertex transformation
;------------------------------------------------------------------------------

; Transform to view space (world matrix is identity)
m4x4 r9, v0, c0	

; 흔드는 부분이다.
mul r10.x,v0.y,c9.x
add r9.x,r9.x,r10.x

; Transform to projection space
m4x4 r10, r9, c4

; Store output position
mov oPos, r10	
mov oD0, v3    ;컬러 값을 넣는다.
mov oD0.w,c9.y		;//알파 조절

;------------------------------------------------------------------------------
; Texture coordinates
;------------------------------------------------------------------------------

; Copy tex coords
mov oT0.xy, v4



;------------------------------------------------------------------------------
; Fog calculation
;------------------------------------------------------------------------------
; compute fog factor f = (fog_end - dist)*(1/(fog_end-fog_start))
add r0.x, -r9.z, c8.y
mul r0.x, r0.x, c8.z
max r0.x, r0.x, c9.z       ; clamp fog to > 0.0
min oFog, r0.x, c9.w     ; clamp fog to < 1.0

;mov oFog.x,c10.x

