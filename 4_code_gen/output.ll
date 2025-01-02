; ModuleID = 'program.bc'
source_filename = "program.bc"

define i32 @main() {
entry:
  %a = alloca float, align 4
  store float 1.500000e+00, ptr %a, align 4
  %a1 = load float, ptr %a, align 4
  %multmp = fmul float 1.000000e+01, %a1
  %convtmp = fptosi float %multmp to i32
  ret i32 %convtmp
}
