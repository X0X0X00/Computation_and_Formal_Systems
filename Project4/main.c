#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snop.h"
#include "pm.h"
#include "psh.h"
#include "pd.h"
#include "pda.h"
#include "pmda.h"


SNOP_HASHTABLE* create_snop() {
//	这里需要声明static类型的变量，否则无法被外界访问到
	static SNOP_HASHTABLE R;
	SNOP_HASHTABLE_init(R);
//	SNOP_HASHTABLE_print(R);
	SNOP_TUPLE* t;
//	972-06-2473 H. Kim Dewey 402 851-3472
//	251-12-6815 E. Price Hutchison 754 896-4408
//	021-08-4448 M. Ruiz CSB 571 360-1897
//	319-97-1535 H. Kim Morey 758 704-9520
//	210-86-2988 J. Jackson Lattimore 879 952-9418
//	098-54-7473 R. Roberts Harkness 156 314-9972
//	101-85-4521 M. Ruiz Hylan 525 470-6491
	t = new_SNOP_TUPLE("972-06-2473", "H. Kim", "Dewey 402", "851-3472");
	SNOP_insert(t, R);
	t = new_SNOP_TUPLE("251-12-6815", "E. Price", "Hutchison 754", "896-4408");
	SNOP_insert(t, R);
	t = new_SNOP_TUPLE("021-08-4448", "M. Ruiz", "CSB 571", "360-1897");
	SNOP_insert(t, R);
	t = new_SNOP_TUPLE("319-97-1535", "H. Kim", "Morey 758", "704-9520");
	SNOP_insert(t, R);
	t = new_SNOP_TUPLE("210-86-2988", "J. Jackson", "Lattimore 879", "952-9418");
	SNOP_insert(t, R);
	t = new_SNOP_TUPLE("098-54-7473", "R. Roberts", "Harkness 156", "314-9972");
	SNOP_insert(t, R);
	t = new_SNOP_TUPLE("101-85-4521", "M. Ruiz", "Hylan525", "470-6491");
	SNOP_insert(t, R);
//	SNOP_HASHTABLE_print(R);
	return &R;
}

PM_HASHTABLE* create_pm() {
	static PM_HASHTABLE R;
	PM_HASHTABLE_init(R);
//	PM_HASHTABLE_print(R);
	PM_TUPLE *t;
//	57849 101-85-4521
	t = new_PM_TUPLE("57849", "101-85-4521");
	PM_insert(t, R);
//	23169 319-97-1535
	t = new_PM_TUPLE("23169", "319-97-1535");
	PM_insert(t, R);
//	99863 210-86-2988
	t = new_PM_TUPLE("99863", "210-86-2988");
	PM_insert(t, R);
//	63653 101-85-4521
	t = new_PM_TUPLE("63653", "101-85-4521");
	PM_insert(t, R);
//	31687 251-12-6815
	t = new_PM_TUPLE("31687", "251-12-6815");
	PM_insert(t, R);
//	72278 210-86-2988
	t = new_PM_TUPLE("72278", "210-86-2988");
	PM_insert(t, R);
	return &R;
}

PDA_HASHTABLE *create_pda() {
	static PDA_HASHTABLE R;
	PDA_HASHTABLE_init(R);
//	PDA_HASHTABLE_print(R);
	PDA_TUPLE *t;
//	63653 Marketing A082
//	99863 Operations N903
//	57849 Support C764
//	99863 Facilities J690
//	72278 Facilities M857
//	31687 Facilities R837
//	57849 Marketing N903
//	23169 Operations J690
	t = new_PDA_TUPLE("63653", "Marketing", "A082");
	PDA_insert(t, R);
	t = new_PDA_TUPLE("99863", "Operations", "N903");
	PDA_insert(t, R);
	t = new_PDA_TUPLE("57849", "Support", "C764");
	PDA_insert(t, R);
	t = new_PDA_TUPLE("99863", "Facilities", "J690");
	PDA_insert(t, R);
	t = new_PDA_TUPLE("72278", "Facilities", "M857");
	PDA_insert(t, R);
	t = new_PDA_TUPLE("31687", "Facilities", "R837");
	PDA_insert(t, R);
	t = new_PDA_TUPLE("57849", "Marketing", "N903");
	PDA_insert(t, R);
	t = new_PDA_TUPLE("23169", "Operations", "J690");
	PDA_insert(t, R);
//	PDA_HASHTABLE_print(R);
	return &R;
}

PD_HASHTABLE *create_pd() {
	static PD_HASHTABLE R;
	PD_HASHTABLE_init(R);
//	PD_HASHTABLE_print(R);
	PD_TUPLE *t;
//	99863 72278
//	57849 63653
//	57849 31687
//	31687 57849
//	63653 23169
	t = new_PD_TUPLE("99863", "72278");
	PD_insert(t, R);
	t = new_PD_TUPLE("57849", "63653");
	PD_insert(t, R);
	t = new_PD_TUPLE("57849", "31687");
	PD_insert(t, R);
	t = new_PD_TUPLE("31687", "57849");
	PD_insert(t, R);
	t = new_PD_TUPLE("63653", "23169");
	PD_insert(t, R);

	return &R;
}

PSH_HASHTABLE *create_psh() {
	static PSH_HASHTABLE R;
	PSH_HASHTABLE_init(R);
	PSH_TUPLE *t;
//	57849 251-12-6815 5.5
//	23169 319-97-1535 6.0
//	63653 021-08-4448 4.0
//	72278 210-86-2988 7.5
//	31687 251-12-6815 4.0
//	99863 319-97-1535 6.0
//	23169 098-54-7473 9.0
//	99863 101-85-4521 5.0
//	31687 101-85-4521 4.0
//	57849 101-85-4521 7.5
//	99863 098-54-7473 4.5
	t = new_PSH_TUPLE("57849", "251-12-6815", 5.5);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("23169", "319-97-1535", 6.0);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("63653", "021-08-4448", 4.0);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("72278", "210-86-2988", 7.5);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("31687", "251-12-6815", 4.0);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("99863", "319-97-1535", 6.0);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("23169", "098-54-7473", 9.0);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("99863", "101-85-4521", 5.0);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("31687", "101-85-4521", 4.0);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("57849", "101-85-4521", 7.5);
	PSH_insert(t, R);
	t = new_PSH_TUPLE("99863", "098-54-7473", 4.5);
	PSH_insert(t, R);
	return &R;
}

double part2_1(char* name, char* project_id) {
    // 1.How many hours does Name work on project ProjectId?
	// create the snop table
	SNOP_HASHTABLE* snop = create_snop();
	// find ssns of Name
	// create query x
	SNOP_TUPLE x;
	strcpy(x.ssn, "");
	strcpy(x.name, name);
	strcpy(x.office, "");
	strcpy(x.phone, "");
//	SNOP_TUPLE_print(&x);
	SNOP_TUPLELIST result = SNOP_lookup(&x, *snop); // all the people with the specified name
	// create the psh table
	PSH_HASHTABLE* psh = create_psh();
	// for each person in result, find the hours with specified project_id
	PSH_TUPLE y;
	strcpy(y.project_id, project_id); // condition 1: project_id
	strcpy(y.ssn, "");
	y.hours = -1;
	// iterate over the result
	double total_hours = 0;
	while (result != NULL) {
		strcpy(y.ssn, result->ssn); // condition 2: ssn
		double hours = 0;
		PSH_TUPLELIST hours_result = PSH_lookup(&y, *psh);
		while (hours_result != NULL) {
			hours += hours_result->hours;
			hours_result = hours_result->next;
		}
		printf("%s works on project %s: %.1f hours\n", name, project_id, hours);
		total_hours += hours;
		result = result->next;
		PSHList_free(hours_result);
	}
	SNOPList_free(result);
	return total_hours;
}



void part2_2(char* name, char* department, char* account) {
	// 2.What is the manager’s SSN of projects involving Name from Department using Account?
	// create table PDA
	PDA_HASHTABLE *pda = create_pda();
	// find project_ids of Name from Department using Account
	PDA_TUPLE y;
	strcpy(y.project_id, "");
	strcpy(y.department, department);
	strcpy(y.account, account);
	PDA_TUPLELIST project_ids = PDA_lookup(&y, *pda);
	PDA_TUPLELIST project_ids_head = project_ids;

	// find the SSNs of Name
	SNOP_HASHTABLE *snop = create_snop();
	PSH_HASHTABLE *psh = create_psh();
	// then find the manager's SSN of the project_ids
	PM_HASHTABLE *pm = create_pm();
	PM_TUPLE z;
	strcpy(z.manager_ssn, "");
	// iterate over project_ids
	while (project_ids != NULL) {
		strcpy(z.project_id, project_ids->project_id); // create new query
		PM_TUPLELIST manager_ssns = PM_lookup(&z, *pm);
		if (manager_ssns != NULL) {
//			manager_ssns->project_id: current testing project id
			// find the involved SSNs in PSH
			PSH_TUPLE psh_query;
			strcpy(psh_query.project_id, manager_ssns->project_id);
			strcpy(psh_query.ssn, "");
			psh_query.hours = -1;
			PSH_TUPLELIST involved_ssns = PSH_lookup(&psh_query, *psh);
			PSH_TUPLELIST involved_ssns_head = involved_ssns;

			// iterate the involved_ssns to find the SSN of Name
			while (involved_ssns != NULL) {
				// find the SSN of Name
				SNOP_TUPLE x;
				strcpy(x.ssn, involved_ssns->ssn);
				strcpy(x.name, "");
				strcpy(x.office, "");
				strcpy(x.phone, "");
				SNOP_TUPLELIST name_result = SNOP_lookup(&x, *snop);
				SNOP_TUPLELIST name_result_head = name_result;
				while (name_result != NULL) {
					if (strcmp(name_result->name, name) == 0) {
						printf("Manager's SSN of projects involving %s from %s using %s: %s\n", name, department, account, manager_ssns->manager_ssn);
					}
					name_result = name_result->next;
				}
				SNOPList_free(name_result_head);
				involved_ssns = involved_ssns->next;
			}
			PSHList_free(involved_ssns_head);
		}
		project_ids = project_ids->next;
	}
	PDAList_free(project_ids_head);

}

void part2() {
	printf("===================== part 2 =====================\n");

	// do this in a REPL loop
	// 1.How many hours does Name work on project ProjectId?
	printf("2.1 Query: How many hours does Name work on project ProjectId?\n");
	printf("Type stop to exit\n");
	while(1) {
		char name[100];
		char project_id[100];
		printf("Enter Name: ");
        fgets(name, 100, stdin);
        // remove the last
        name[strlen(name) - 1] = '\0';
		if (strcmp(name, "stop") == 0) {
			break;
		}
		printf("Enter ProjectId: ");
        fgets(project_id, 100, stdin);
        project_id[strlen(project_id) - 1] = '\0';
		if (strcmp(project_id, "stop") == 0) {
			break;
		}
		part2_1(name, project_id);
//		double hours = part2_1(name, project_id);
//		printf("%s works on project %s: %f hours\n", name, project_id, hours);
	}


	// 2.What is the manager’s SSN of projects involving Name from Department using Account?
	printf("2.2 Query: What is the manager’s SSN of projects involving Name from Department using Account?\n");
	printf("Type stop to exit\n");
	while(1) {
		char name[100];
		char department[100];
		char account[100];
		printf("Enter Name: ");
        fgets(name, 100, stdin);
		name[strlen(name) - 1] = '\0';
		if (strcmp(name, "stop") == 0) {
			break;
		}
		printf("Enter Department: ");
		fgets(department, 100, stdin);
		department[strlen(department) - 1] = '\0';
		if (strcmp(department, "stop") == 0) {
			break;
		}
		printf("Enter Account: ");
        fgets(account, 100, stdin);
		account[strlen(account) - 1] = '\0';
		if (strcmp(account, "stop") == 0) {
			break;
		}
		part2_2(name, department, account);
	}

}


PMDA_HASHTABLE *PM_join_PDA(PM_HASHTABLE pm_table, PDA_HASHTABLE pda_table) {
	static PMDA_HASHTABLE R;
	PMDA_HASHTABLE_init(R);
	// iterate over the pm_table and find the project_id in pda_table
	for (int i = 0; i < PM_HASHTABLE_SIZE; i++) {
		PM_TUPLE *p = pm_table[i];
		while (p != NULL) {
			PDA_TUPLE y;
			strcpy(y.project_id, p->project_id);
			strcpy(y.department, "");
			strcpy(y.account, "");
			PDA_TUPLELIST project_ids = PDA_lookup(&y, pda_table);
			PDA_TUPLELIST project_ids_head = project_ids;
			while (project_ids != NULL) {
				PMDA_TUPLE *t = new_PMDA_TUPLE(p->project_id, p->manager_ssn, project_ids->department, project_ids->account);
				PMDA_insert(t, R);
				project_ids = project_ids->next;
			}
			p = p->next;
			PDAList_free(project_ids_head);
		}
	}
	return &R;
}

PSH_TUPLELIST select_PSH_ProjectId(char* project_id, PSH_HASHTABLE psh) {
	PSH_TUPLE x;
	strcpy(x.project_id, project_id);
	strcpy(x.ssn, "");
	x.hours = -1;
	PSH_TUPLELIST result = PSH_lookup(&x, psh);
//	while (result != NULL) {
//		printf("project_id: %s, ssn: %s, hours: %f\n", result->project_id, result->ssn, result->hours);
//		result = result->next;
//	}
	return result;
}

Name_TUPLELIST project_SNOP_Name(SNOP_HASHTABLE snop) {
	SNOP_TUPLE x;
	strcpy(x.ssn, "");
	strcpy(x.name, "");
	strcpy(x.office, "");
	strcpy(x.phone, "");
	SNOP_TUPLELIST result = SNOP_lookup(&x, snop);
	// do projection: construct Name_TUPLELIST
	Name_TUPLELIST name_result = NULL;
	while (result != NULL) {
		Name_TUPLE *t = new_Name_TUPLE(result->name);
		if (name_result == NULL) {
			name_result = t;
		}
		else {
			Name_TUPLE *p = name_result;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = t;
		}
		result = result->next;
	}
	return name_result;
}

PMDA_TUPLELIST select_PMDA_ManagerSsn(char* manager_ssn, PMDA_HASHTABLE pmda) {
	PMDA_TUPLE x;
	strncpy(x.project_id, "", sizeof(x.project_id) - 1);
	x.project_id[sizeof(x.project_id) - 1] = '\0';
	strncpy(x.manager_ssn, manager_ssn, sizeof(x.manager_ssn) - 1);
	x.manager_ssn[sizeof(x.manager_ssn) - 1] = '\0';
	strncpy(x.department, "", sizeof(x.department) - 1);
	x.department[sizeof(x.department) - 1] = '\0';
	strncpy(x.account, "", sizeof(x.account) - 1);
	x.account[sizeof(x.account) - 1] = '\0';


	PMDA_TUPLELIST result = PMDA_lookup(&x, pmda);
//	while (result != NULL) {
//		printf("project_id: %s, manager_ssn: %s, department: %s, account: %s\n", result->project_id, result->manager_ssn, result->department, result->account);
//		result = result->next;
//	}
	return result;
}

DA_TUPLELIST project_PMDA_DA(PMDA_TUPLELIST result) {
	DA_TUPLELIST da_result = NULL;
	while (result != NULL) {
		DA_TUPLE *t = new_DA_TUPLE(result->department, result->account);
		if (da_result == NULL) {
			da_result = t;
		}
		else {
			DA_TUPLE *p = da_result;
			while (p->next != NULL) {
				p = p->next;
			}
			p->next = t;
		}
		result = result->next;
	}
	return da_result;
}

void part1() {
	printf("===================== part 1 =====================\n");
	// create psh table
	PSH_HASHTABLE *psh = create_psh();
	SNOP_HASHTABLE *snop = create_snop();
	PD_HASHTABLE *pd = create_pd();
	PM_HASHTABLE *pm = create_pm();
	PDA_HASHTABLE *pda = create_pda();
//	(a) lookup( ⟨ 99863, “319-97-1535”, ∗ ⟩ , ProjectId-SSN-Hours)
	printf("(a) lookup( ⟨ 99863, “319-97-1535”, ∗ ⟩ , ProjectId-SSN-Hours)\n");
	PSH_TUPLE x1;
	strcpy(x1.project_id, "99863");
	strcpy(x1.ssn, "319-97-1535");
	x1.hours = -1;
	PSH_TUPLELIST result = PSH_lookup(&x1, *psh);
	while (result != NULL) {
		printf("project_id: %s, ssn: %s, hours: %f\n", result->project_id, result->ssn, result->hours);
		result = result->next;
	}
//	(b) lookup( ⟨ ∗, “H. Kim”, ∗, ∗ ⟩ , SSN-Name-Office-Phone)
	printf("(b) lookup( ⟨ ∗, “H. Kim”, ∗, ∗ ⟩ , SSN-Name-Office-Phone)\n");
	SNOP_TUPLE x2;
	strcpy(x2.ssn, "");
	strcpy(x2.name, "H. Kim");
	strcpy(x2.office, "");
	strcpy(x2.phone, "");
	SNOP_TUPLELIST result2 = SNOP_lookup(&x2, *snop);
	while (result2 != NULL) {
		printf("ssn: %s, name: %s, office: %s, phone: %s\n", result2->ssn, result2->name, result2->office, result2->phone);
		result2 = result2->next;
	}

//	(c) lookup( ⟨ 12345, 67890 ⟩ , ProjectId-DependsOn)
	printf("(c) lookup( ⟨ 12345, 67890 ⟩ , ProjectId-DependsOn)\n");
	PD_TUPLE x3;
	strcpy(x3.project_id, "12345");
	strcpy(x3.depends_on, "67890");
	PD_TUPLELIST result3 = PD_lookup(&x3, *pd);
	while (result3 != NULL) {
		printf("project_id: %s, depends_on: %s\n", result3->project_id, result3->depends_on);
		result3 = result3->next;
	}

//	(d) delete( ⟨ 63653, “101-85-4521” ⟩ , ProjectId-ManagerSSN)
	printf("(d) delete( ⟨ 63653, “101-85-4521” ⟩ , ProjectId-ManagerSSN)\n");
	PM_TUPLE x4;
	strcpy(x4.project_id, "63653");
	strcpy(x4.manager_ssn, "101-85-4521");
	PM_delete(&x4, *pm);

//	(e) delete( ⟨ 72278, “Facilities”, “P123” ⟩ , ProjectId-Department-Account)
	printf("(e) delete( ⟨ 72278, “Facilities”, “P123” ⟩ , ProjectId-Department-Account)\n");
	PDA_TUPLE x5;
	strcpy(x5.project_id, "72278");
	strcpy(x5.department, "Facilities");
	strcpy(x5.account, "P123");
	PDA_delete(&x5, *pda);

//	(f) delete( ⟨ 72278, ∗, ∗ ⟩ , ProjectId-Department-Account)
	printf("(f) delete( ⟨ 72278, ∗, ∗ ⟩ , ProjectId-Department-Account)\n");
	PDA_TUPLE x6;
	strcpy(x6.project_id, "72278");
	strcpy(x6.department, "");
	strcpy(x6.account, "");
	PDA_delete(&x6, *pda);
//	(g) insert( ⟨ 23169, 57849 ⟩ , ProjectId-DependsOn)
	printf("(g) insert( ⟨ 23169, 57849 ⟩ , ProjectId-DependsOn)\n");
	PD_TUPLE x7;
	strcpy(x7.project_id, "23169");
	strcpy(x7.depends_on, "57849");
	PD_insert(&x7, *pd);

//	(h) insert( ⟨ 57849, 31687 ⟩ , ProjectId-DependsOn)
	printf("(h) insert( ⟨ 57849, 31687 ⟩ , ProjectId-DependsOn)\n");
	PD_TUPLE x8;
	strcpy(x8.project_id, "57849");
	strcpy(x8.depends_on, "31687");
	PD_insert(&x8, *pd);
}

void part3() {
	printf("===================== part 3 =====================\n");
	// 1.selection project_id == 99863 in PSH
	printf("===================== 3.1 =====================\n");
	PSH_HASHTABLE *psh = create_psh();
//	PSH_HASHTABLE_print(*psh);
	PSH_TUPLELIST result = select_PSH_ProjectId("99863", *psh);
	PSH_TUPLELIST_print(result);

	// 2.projection name on SNOP
	printf("===================== 3.2 =====================\n");
	SNOP_HASHTABLE *snop = create_snop();
	Name_TUPLELIST name_result = project_SNOP_Name(*snop);
	Name_TUPLE_print(name_result);

	// 3.Join PM and PDA
	printf("===================== 3.3 =====================\n");
	PM_HASHTABLE *pm = create_pm();
	PDA_HASHTABLE *pda = create_pda();
	// join the table PM and PDA into a pmda table
	PMDA_HASHTABLE *pmda = PM_join_PDA(*pm, *pda);
	PMDA_HASHTABLE_print(*pmda);

	printf("===================== 3.4 =====================\n");
	// 4.All three operators
	// 4.1 join PM and PDA => pmda
	// 4.2 select manager_ssn == 210-86-2988
	PMDA_TUPLELIST result2 = select_PMDA_ManagerSsn("210-86-2988", *pmda);
	// 4.3 do projection on Department and Account
	DA_TUPLELIST da_result = project_PMDA_DA(result2);
	DA_TUPLELIST_print(da_result);

}


void test() {
	part1();
	part2_1("J. Jackson", "72278"); // 7.5
	part2_2("E. Price", "Facilities", "R837"); // 31687
	part3();
}


int main(int argc, char** argv) {
	part1();
	part2();
	part3();
//	test();
}



