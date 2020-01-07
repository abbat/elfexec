Name:          elfexec
Version:       0.3
Release:       1
Summary:       Utility to execute ELF binary directly from stdin pipe
Group:         Productivity/File utilities
License:       BSD-2-Clause
URL:           https://github.com/abbat/elfexec
Source0:       https://build.opensuse.org/source/home:antonbatenev:elfexec/elfexec/elfexec_%{version}.tar.bz2
BuildRoot:     %{_tmppath}/%{name}-%{version}-build


%description
Utility to execute ELF binary directly from stdin pipe.


%prep
%setup -q -n elfexec


%build
make USER_CFLAGS="${RPM_OPT_FLAGS}" USER_CPPFLAGS="${RPM_OPT_FLAGS}" USER_LDFLAGS="${RPM_LD_FLAGS}" %{?_smp_mflags}


%install

install -d %{buildroot}%{_bindir}

install -m755 elfexec %{buildroot}%{_bindir}/elfexec

install -d %{buildroot}%{_mandir}/man1

install -m644 elfexec.1 %{buildroot}%{_mandir}/man1/elfexec.1


%clean
rm -rf %{buildroot}


%files
%defattr(-,root,root,-)
%doc README.md
%doc %{_mandir}/man1/elfexec.1*

%{_bindir}/elfexec


%changelog
* Tue Jan 07 2020 Anton Batenev <antonbatenev@yandex.ru> 0.3-1
- Initial RPM release
