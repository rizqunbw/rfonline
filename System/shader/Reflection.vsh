
vs.1.1
;------------------------------------------------------------------------------
; c0-c3 매트릭스 1 
; c4-c7 매트릭스 2
; c8	포그
; c9  x=흔들수치 ,y=알파
; c10  	바닥컬러 
; c12- 버텍스 쉐이더의 상황에 따른 셋팅.
;
; Vertex components 
;    v0    = Position
;------------------------------------------------------------------------------

dcl_position0	v0
dcl_color		v6
dcl_texcoord0	v3

;------------------------------------------------------------------------------
; Vertex transformation
;------------------------------------------------------------------------------

; Transform to view space (world matrix is identity)
m4x4 r9, v0, c0	

; Transform to projection space
m4x4 r10, v0, c4

; Store output position
mov oPos, r10	

;mul oD0,v6,c10       ;Diffuse *바닥컬러
;mov oD0.w,c9.y		;//알파 조절
;mov oD0, v6    ;컬러 값을 넣는다.
mov oD0, c10    ;컬러 값을 넣는다.
mov oD1, c10    ;컬러 값을 넣는다.
;------------------------------------------------------------------------------
; Texture coordinates
;------------------------------------------------------------------------------

; Copy tex coords
mov oT0.xy, v3

dp4 r0.x, v0, c14
dp4 r0.y, v0, c15
dp4 r0.z, v0, c16

rcp r0.z, r0.z
mad oT1.x,r0.x,r0.z,c11.w
mad oT1.y,r0.y,r0.z,c11.z


;mul r9,c11,r10
;add r9.x,r9.x,c11.z
;add r9.y,r9.y,c11.w
;mov oT1.x,r9.x
;mov oT1.y,r9.y


;------------------------------------------------------------------------------
; Fog calculation
;------------------------------------------------------------------------------
; compute fog factor f = (fog_end - dist)*(1/(fog_end-fog_start))
add r0.x, -r9.z, c8.y
mul r0.x, r0.x, c8.z
max r0.x, r0.x, c9.z       ; clamp fog to > 0.0
min oFog, r0.x, c9.w     ; clamp fog to < 1.0

;mov oFog.x,c10.x

