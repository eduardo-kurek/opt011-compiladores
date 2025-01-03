; ModuleID = 'program.bc'
source_filename = "program.bc"

define i32 @main() {
entry:
  %a = alloca float, align 4
  %b = alloca float, align 4
  store float 5.500000e+00, ptr %a, align 4
  %a1 = load float, ptr %a, align 4
  %addtmp = fadd float %a1, 2.000000e+00
  store float %addtmp, ptr %b, align 4
}
