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
  %b2 = load float, ptr %b, align 4
  %a3 = load float, ptr %a, align 4
  %cmptmp = fcmp olt float %a3, %b2
  %ortmp = or i1 %cmptmp, true
  br i1 %ortmp, label %then, label %end

then:                                             ; preds = %entry
  %a4 = load float, ptr %a, align 4
  %float2int = fptosi float %a4 to i32
  ret i32 %float2int
  br label %end

end:                                              ; preds = %then, %entry
  %b5 = load float, ptr %b, align 4
  %a6 = load float, ptr %a, align 4
  %multmp = fmul float %a6, %b5
  %convtmp = fptosi float %multmp to i32
  ret i32 %convtmp
  ret i32 0
}
